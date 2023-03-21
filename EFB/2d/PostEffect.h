#pragma once
#include "Sprite.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "../input/Input.h"
#include "../Map/MapChip.h"

class PostEffect : public Sprite
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PostEffect();

	void Initialize();

	void Draw(ID3D12GraphicsCommandList*cmdList, bool stopFlag);

	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	void CreateGraphicsPipelineState();
protected:
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;

	// パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelineState;

	ComPtr<ID3D12Resource> texBuff[2];
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	ComPtr<ID3D12Resource> depthBuff;
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	static const float clearColor[4];
};

