#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include "WinApp.h"

class DirectXCommon
{
private: // �G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initialize(WinApp *win);

	void PreDraw();

	void PostDraw();

	void ClearRenderTarget();

	void ClearDepthBuffer();

	ID3D12Device *GetDevice() { return dev.Get(); }

	ID3D12GraphicsCommandList *GetCommandList() { return cmdList.Get(); }
private: // �����o�ϐ�
// �E�B���h�E�Y�A�v���P�[�V�����Ǘ�
	WinApp *winApp;

	// Direct3D�֘A
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
private: // �����o�֐�

	bool InitializeDXGIDevice();//DXGI�f�o�C�X

	bool CreateSwapChain();//�X���b�v�`�F�[��

	bool InitializeCommand();//�R�}���h������

	bool CreateFinalRenderTargets();//�����_�[�^�[�Q�b�g

	bool CreateDepthBuffer();//�[�x�o�b�t�@

	bool CreateFence();//�t�F���X����
};