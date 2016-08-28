#include "BlankWindowDemo.h"

BlankWindowDemo::BlankWindowDemo() {}

BlankWindowDemo::~BlankWindowDemo() {}

bool BlankWindowDemo::LoadContent() {
	return true;
}

void BlankWindowDemo::UnloadContent() {}

void BlankWindowDemo::Update(float DeltaTime) {}

void BlankWindowDemo::Render() {

	float quitColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (d3dDeviceContext_ == nullptr) return;									// Pointer protection
	d3dDeviceContext_->ClearRenderTargetView(backBufferTarget_, quitColor);
	swapChain_->Present(0, 0);
}