#include "PostEffect.h"
#include<d3dx12.h>

using namespace DirectX;

PostEffect::PostEffect() 
	: Sprite(
	100,
	{0,0},
	{ 500,500 },
	{ 1,1,1,1 },
	{ 0.0f,0.0f },
	false,
	false)
{
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
	this->matWorld = XMMatrixIdentity();

	this->matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));

	this->matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->mat = matWorld * matProjection;
		constMap->color = color;
		constBuff->Unmap(0, nullptr);
	}

	cmdList->SetPipelineState(pipelineState.Get());

	cmdList->SetGraphicsRootSignature(rootSignature.Get());

	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	cmdList->IASetVertexBuffers(0, 1, &vbView);

	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };

	// デスクリプタヒープをセット
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	cmdList->SetGraphicsRootConstantBufferView(0, this->constBuff->GetGPUVirtualAddress());

	//シェーダリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(
			descHeap->GetGPUDescriptorHandleForHeapStart(),
			this->texNumber, descriptorHandleIncrementSize));


	cmdList->DrawInstanced(4, 1, 0, 0);
}
