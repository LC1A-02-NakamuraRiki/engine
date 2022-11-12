#include "Object3d.h"
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;
#include <fstream>	
#include <sstream>	
#include <string>	
#include <vector>

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device *Object3d::device = nullptr;
ID3D12GraphicsCommandList *Object3d::cmdList = nullptr;
Object3d::PipelineSet Object3d::pipelineSet;
Camera *Object3d::camera = nullptr;
LightGroop *Object3d::lightGroup = nullptr;

void Object3d::StaticInitialize(ID3D12Device *device,Camera *camera)
{
	Object3d::device = device;
	Object3d::camera = camera;

	// パイプライン初期化
	InitializeGraphicsPipeline();

	Model::StaticInitialize(device);
}

void Object3d::InitializeGraphicsPipeline()
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/OBJVS.hlsl",  // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/OBJPS.hlsl",   // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char *)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{  //xyz座標
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}, // (1行で書いたほうが見やすい)

		{  //法線ベクトル
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}, // (1行で書いたほうが見やすい)

		{  //uv座標
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}, // (1行で書いたほうが見やすい)
	};

	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// 標準設定(背面カリング、塗りつぶし、深度クリッピング有効)
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

	//デプスステンシルステートの設定
	//標準設定(深度テストを行う、書き込み許可、小さければ合格)
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; //標準設定
	blenddesc.BlendEnable = true;                 //ブレンドを有効にする
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;  //加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;   //ソースの値を100%使う
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; //デストの値を  0%使う

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1; // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0～255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	//デスクリプタテーブルの設定
	CD3DX12_DESCRIPTOR_RANGE descTblRangeSRV;
	descTblRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);  //t0 レジスタ

	// ルートパラメータ	
	CD3DX12_ROOT_PARAMETER rootparams[4];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsDescriptorTable(1, &descTblRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[3].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);
	
	// スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定のシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ルートシグネチャの生成
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&pipelineSet.rootsignature));

	gpipeline.pRootSignature = pipelineSet.rootsignature.Get();

	// グラフィックスパイプラインの生成
	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineSet.pipelinestate));

}

void Object3d::PreDraw(ID3D12GraphicsCommandList *cmdList)
{
	// コマンドリストをセット
	Object3d::cmdList = cmdList;
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3d::PostDraw()
{
	Object3d::cmdList = nullptr;
}

Object3d *Object3d::Create(Model *model)
{
	Object3d *object3d = new Object3d();
	if (object3d == nullptr) {
		return nullptr;
	}
	//スケールをセット	// 初期化
	float scale_val = 1;
	object3d->scale = { scale_val, scale_val, scale_val };
	// 初期化
		if (!object3d->Initialize()) {
			delete object3d;
			assert(0);
		}
		if (model) {
			object3d->LinkModel(model);
		}
	return object3d;
}

bool Object3d::Initialize()
{
	HRESULT result;

	//定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), //アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));

	constBuffB0->SetName(L"EZEZEZEZEZEZEZEZ");

	return true;
}

void Object3d::Update(XMFLOAT3 shadowPos)
{
	assert(camera);

	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	if (isBillboard) {
		const XMMATRIX &matBillboard = camera->GetBillboardMatrix();

		matWorld = XMMatrixIdentity();
		matWorld *= matScale; // ワールド行列にスケーリングを反映
		matWorld *= matRot; // ワールド行列に回転を反映
		matWorld *= matBillboard;
		matWorld *= matTrans; // ワールド行列に平行移動を反映
	}

	// 親オブジェクトがあれば
	if (parent != nullptr) {
		// 親オブジェクトのワールド行列を掛ける
		matWorld *= parent->matWorld;
	}

	const XMMATRIX &matViewProjection = camera->GetViewProjectionMatrix();
	const XMFLOAT3 &cameraPos = camera->GetEye();
	const XMFLOAT3& cameraPos2 = camera->GetEye();
	// 定数バッファへデータ転送
	ConstBufferDataB0 *constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void **)&constMap);
	//constMap->mat = matWorld * matViewProjection;	// 行列の合成
	constMap->viewproj = matViewProjection;
	constMap->world = matWorld;
	constMap->cameraPos = cameraPos;
	constMap->shadowPos = shadowPos;
	
	 constMap->lightScale0 = 1;
	 constMap->lightScale1 = 1;
	 constMap->lightScale2 = 1;
	 constMap->lightScale3 = 1;
	 constMap->lightScale4 = 1;
	 constMap->lightScale5 = 1;
	 constMap->lightScale6 = 1;
	 constMap->lightScale7 = 1;
	 constMap->lightScale8 = 1;
	 constMap->lightScale9 = 1;
	constMap->lightScale10 = 1;
	constMap->lightScale11 = 1;
	constMap->lightScale12 = 1;
	constMap->lightScale13 = 1;
	constMap->lightScale14 = 1;
	constMap->lightScale15 = 1;
	constMap->lightScale16 = 1;
	constMap->lightScale17 = 1;
	constMap->lightScale18 = 1;
	constMap->lightScale19 = 1;
	constMap->lightScale20 = 1;
	constMap->lightScale21 = 1;
	constMap->lightScale22 = 1;
	constMap->lightScale23 = 1;
	constMap->lightScale24 = 1;
	constMap->lightScale25 = 1;
	constMap->lightScale26 = 1;
	constMap->lightScale27 = 1;
	constMap->lightScale28 = 1;
	constMap->lightScale29 = 1;
	constMap->lightScale30 = 1;
	constMap->lightScale31 = 1;
	constMap->lightScale32 = 1;
	constMap->lightScale33 = 1;
	constMap->lightScale34 = 1;
	constMap->lightScale35 = 1;
	constMap->lightScale36 = 1;
	constMap->lightScale37 = 1;
	constMap->lightScale38 = 1;
	constMap->lightScale39 = 1;
	constMap->lightScale40 = 1;
	constMap->lightScale41 = 1;
	constMap->lightScale42 = 1;
	constMap->lightScale43 = 1;
	constMap->lightScale44 = 1;
	constMap->lightScale45 = 1;
	constMap->lightScale46 = 1;
	constMap->lightScale47 = 1;
	constMap->lightScale48 = 1;

	constBuffB0->Unmap(0, nullptr);
}

void Object3d::LightUpdate(XMFLOAT3 shadowPos)
{
	assert(camera);

	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); // 変形をリセット
	matWorld *= matScale; // ワールド行列にスケーリングを反映
	matWorld *= matRot; // ワールド行列に回転を反映
	matWorld *= matTrans; // ワールド行列に平行移動を反映

	if (isBillboard) {
		const XMMATRIX &matBillboard = camera->GetBillboardMatrix();

		matWorld = XMMatrixIdentity();
		matWorld *= matScale; // ワールド行列にスケーリングを反映
		matWorld *= matRot; // ワールド行列に回転を反映
		matWorld *= matBillboard;
		matWorld *= matTrans; // ワールド行列に平行移動を反映
	}

	// 親オブジェクトがあれば
	if (parent != nullptr) {
		// 親オブジェクトのワールド行列を掛ける
		matWorld *= parent->matWorld;
	}

	const XMMATRIX &matViewProjection = camera->GetViewProjectionMatrix();
	const XMFLOAT3 &cameraPos = camera->GetEye();
	const XMFLOAT3& cameraPos2 = camera->GetEye();
	// 定数バッファへデータ転送
	ConstBufferDataB0 *constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void **)&constMap);
	//constMap->mat = matWorld * matViewProjection;	// 行列の合成
	constMap->viewproj = matViewProjection;
	constMap->world = matWorld;
	constMap->cameraPos = cameraPos;
	constMap->shadowPos = shadowPos;
	
	  constMap->lightScale0 = 9;
	  constMap->lightScale1 = 9;
	  constMap->lightScale2 = 9;
	  constMap->lightScale3 = 9;
	  constMap->lightScale4 = 9;
	  constMap->lightScale5 = 9;
	  constMap->lightScale6 = 9;
	  constMap->lightScale7 = 9;
	  constMap->lightScale8 = 9;
	  constMap->lightScale9 = 9;
	 constMap->lightScale10 = 9;
	 constMap->lightScale11 = 9;
	 constMap->lightScale12 = 9;
	 constMap->lightScale13 = 9;
	 constMap->lightScale14 = 9;
	 constMap->lightScale15 = 9;
	 constMap->lightScale16 = 9;
	 constMap->lightScale17 = 9;
	 constMap->lightScale18 = 9;
	 constMap->lightScale19 = 9;
	 constMap->lightScale20 = 9;
	 constMap->lightScale21 = 9;
	 constMap->lightScale22 = 9;
	 constMap->lightScale23 = 9;
	 constMap->lightScale24 = 9;
	 constMap->lightScale25 = 9;
	 constMap->lightScale26 = 9;
	 constMap->lightScale27 = 9;
	 constMap->lightScale28 = 9;
	 constMap->lightScale29 = 9;
	 constMap->lightScale30 = 9;
	 constMap->lightScale31 = 9;
	 constMap->lightScale32 = 9;
	 constMap->lightScale33 = 9;
	 constMap->lightScale34 = 9;
	 constMap->lightScale35 = 9;
	 constMap->lightScale36 = 9;
	 constMap->lightScale37 = 9;
	 constMap->lightScale38 = 9;
	 constMap->lightScale39 = 9;
	 constMap->lightScale40 = 9;
	 constMap->lightScale41 = 9;
	 constMap->lightScale42 = 9;
	 constMap->lightScale43 = 9;
	 constMap->lightScale44 = 9;
	 constMap->lightScale45 = 9;
	 constMap->lightScale46 = 9;
	 constMap->lightScale47 = 9;
	 constMap->lightScale48 = 9;

	constBuffB0->Unmap(0, nullptr);
}

void Object3d::Draw()
{
	// モデルの割り当てがなければ描画しない
	if (model == nullptr) {
		return;
	}

	// パイプラインステートの設定
	cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	// ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
	// 定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	lightGroup->Draw(cmdList, 3);
	// モデル描画
	model->Draw(cmdList);
}

float Object3d::SetLightAllActive()
{
	return lightActive[0] = 1;
}

float Object3d::SetLightAllNoActive()
{
	return lightActive[0] = 0;
}
