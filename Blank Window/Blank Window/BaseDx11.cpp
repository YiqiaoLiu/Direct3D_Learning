#include "BaseDx11.h"
#include <stdio.h>
int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;

BaseDx11::BaseDx11() : backBufferTarget_(nullptr), swapChain_(nullptr), d3dDevice_(nullptr), d3dDeviceContext_(nullptr),
driverType_(D3D_DRIVER_TYPE_NULL), featureLevel_(D3D_FEATURE_LEVEL_11_0) {}

BaseDx11::~BaseDx11() {}

bool BaseDx11::LoadContent() {
	return true;
}

void BaseDx11::UnloadContent() {}

void BaseDx11::Update(float DeltaTime) {}

void BaseDx11::Render() {
	float quitColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	d3dDeviceContext_->ClearRenderTargetView(backBufferTarget_, quitColor);
	swapChain_->Present(0, 0);
}

bool BaseDx11::InitializeSetting(HWND hwnd) {

	// Set the rect area of the window based on the main.cpp
	RECT rc;
	GetClientRect(hwnd, &rc);
	unsigned int windowWidth = rc.right - rc.left;
	unsigned int windowHeight = rc.bottom - rc.top;

	// The array stores all the types of the driver
	D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_WARP };
	unsigned int totalDriverType = ARRAYSIZE(driverTypes);
	//DXTRACE_MSG(totalDriverType);

	// The array stores several feature levels
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_10_1};
	unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);

	// Set the swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;													// Set the number of back buffer
	swapChainDesc.BufferDesc.Height = windowHeight;
	swapChainDesc.BufferDesc.Width = windowWidth;									// Set the size of the back buffer. Ensure it is the same as the front buffer
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;							// Set the refresh rate of the buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;					// Set the format of the buffer
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;					// Set the buffer could be rendered
	swapChainDesc.OutputWindow = hwnd;												// Set the output window
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int createDeviceFlag = 0;
#ifdef _DEBUG
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT tempResult;
	unsigned int currentDriver = 0;

	// Create the device and swap chain in the loop in order to find the right driver type.
	for (currentDriver = 0; currentDriver < totalDriverType; currentDriver++) {

		// Create the d3d device
		tempResult = D3D11CreateDeviceAndSwapChain(
			0, driverTypes[currentDriver], 0, createDeviceFlag, 
			featureLevels, totalFeatureLevels ,
			D3D11_SDK_VERSION, &swapChainDesc, &swapChain_, 
			&d3dDevice_, &featureLevel_, &d3dDeviceContext_
		);

		// If create succeeded, store the right diver type
		if (SUCCEEDED(tempResult)) {
			driverType_ = driverTypes[currentDriver];
			break;
		}
	}

	// If cannot create the device and swap chain, return
	if (FAILED(tempResult)) {
		DXTRACE_MSG("Fail to create device and swap chain");
		return false;
	}

	// Bind the swap chain and the back buffer
	ID3D11Texture2D* backBufferTexture;
	tempResult = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& backBufferTexture);
	if (FAILED(tempResult)) {
		DXTRACE_MSG("Failed to get the swap chain buffer!");
		return false;
	}

	// Create the render target view
	tempResult = d3dDevice_->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget_);
	if (backBufferTexture) backBufferTexture->Release();										// Release the texture
	if (FAILED(tempResult)) {
		DXTRACE_MSG("Failed to create the render target view");
		return false;
	}

	d3dDeviceContext_->OMSetRenderTargets(1, &backBufferTarget_, nullptr);

	// Create the viewport
	D3D11_VIEWPORT mViewport;
	mViewport.Height = static_cast<float>(windowHeight);
	mViewport.Width = static_cast<float>(windowWidth);
	mViewport.MaxDepth = 1.0;
	mViewport.MinDepth = 0.0;
	mViewport.TopLeftX = 0.0;
	mViewport.TopLeftY = 0.0;
	d3dDeviceContext_->RSSetViewports(1, &mViewport);

	// Load the content
	return LoadContent();


}

void BaseDx11::CloseWindow() {

	// First, Unload the window content
	UnloadContent();

	// Second, release the component 
	if (backBufferTarget_) backBufferTarget_->Release();
	if (swapChain_) swapChain_->Release();
	if (d3dDevice_) d3dDevice_->Release();
	if (d3dDeviceContext_) d3dDeviceContext_->Release();

	// Third, reset the component
	backBufferTarget_ = nullptr;
	swapChain_ = nullptr;
	d3dDevice_ = nullptr;
	d3dDeviceContext_ = nullptr;

}