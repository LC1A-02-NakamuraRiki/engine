#include "LightGroop.h"
#include <assert.h>

using namespace DirectX;

ID3D12Device* LightGroop::device = nullptr;

void LightGroop::StaticInitialize(ID3D12Device* device)
{
	// 再初期化チェック
	assert(!LightGroop::device);

	// nullptrチェック
	assert(device);

	LightGroop::device = device;
}

LightGroop* LightGroop::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	LightGroop* instance = new LightGroop();

	// 初期化
	instance->Initialize();

	return instance;
}

void LightGroop::Initialize()
{
	HRESULT result;
	DefaultLightSetting();
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));

	if (FAILED(result)) { assert(0); }
	TransferConstBuffer();
}

void LightGroop::Update()
{
	if (dirty) {
		TransferConstBuffer();
		dirty = false;
	}
}

void LightGroop::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}

void LightGroop::TransferConstBuffer()
{
	HRESULT result;
	// 定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->ambientColor = ambientColor;
		for (int i = 0; i < DirLightNum; i++) {
			// ライトが有効なら設定を転送
			if (dirLights[i].IsActive()) {
				constMap->dirLights[i].active = 1;
				constMap->dirLights[i].lightv = -dirLights[i].GetLightDir();
				constMap->dirLights[i].lightcolor = dirLights[i].GetLightColor();
			}
			// ライトが無効ならライト色を0に
			else {
				constMap->dirLights[i].active = 0;
			}
		}
		constBuff->Unmap(0, nullptr);
	}
}

void LightGroop::DefaultLightSetting()
{
	for (int i = 0; i < 6; i++)
	{
		if (i == 0 || i == 5){//ライトの向きが上下だった時
			dirLights[i].SetActive(true);
			dirLights[i].SetLightColor(lightColorUpDown);
			dirLights[i].SetLightDir(lightDir[i]);
		}
		else{//ライトの向きが横向きだった時
			dirLights[i].SetActive(true);
			dirLights[i].SetLightColor(lightColorSide);
			dirLights[i].SetLightDir(lightDir[i]);
		}
	}
}

void LightGroop::SetAmbientColor(const XMFLOAT3& color)
{
	ambientColor = color;
	dirty = true;
}

void LightGroop::SetDirLightActive(int index, bool active)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetActive(active);
}

void LightGroop::SetDirLightDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetLightDir(lightdir);
	dirty = true;
}

void LightGroop::SetDirLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetLightColor(lightcolor);
	dirty = true;
}

