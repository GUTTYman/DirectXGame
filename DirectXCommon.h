#include"WinApp.h"

#include<d3d12.h> 
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<vector>
#include<wrl.h>

#pragma once
class DirectXCommon
{
public:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(WinApp* winApp);
	/// <summary>
	/// •`‰æ‘Oˆ—
	/// </summary>
	void BeginDraw();
	/// <summary>
	/// •`‰æŒãˆ—
	/// </summary>
	void EndDraw();

	ID3D12Device* GetDevice() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }

private:
	WinApp* winApp = nullptr;

	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	std::vector<ComPtr<ID3D12Resource>>backBuffers;
	ComPtr< ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeaps;

	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;


};

