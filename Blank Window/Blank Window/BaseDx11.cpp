#include "BaseDx11.h"

BaseDx11::BaseDx11() : backBufferTarget_(nullptr), swapChain_(nullptr), d3dDevice_(nullptr), d3dDeviceContext_(nullptr),
driverType_(D3D_DRIVER_TYPE_NULL), featureLevel_(D3D_FEATURE_LEVEL_11_0) {}

BaseDx11::~BaseDx11() {}

bool BaseDx11::LoadContent() {
	return true;
}

void BaseDx11::UnloadContent() {}

void BaseDx11::Update(float DeltaTime) {}

void BaseDx11::Render() {}

void BaseDx11::InitializeSetting(HWND hwnd) {

	// Set the rect area of the window based on the main.cpp
	RECT rc;
	GetClientRect(hwnd, &rc);
	unsigned int windowWidth = rc.right - rc.left;
	unsigned int windowHeight = rc.top - rc.bottom;

	// The array stores all the types of the driver
	D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_WARP };
	unsigned int totalDriverType = ARRAYSIZE(driverTypes);

	// The array stores several feature levels
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0};
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