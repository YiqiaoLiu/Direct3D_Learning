#include "DrawTriangleDemo.h"

DrawTriangleDemo::DrawTriangleDemo() : triangleVertexShader_(nullptr), trianglePixelShader_(nullptr), triangleInputLayout_(nullptr), triangleBuffer_(nullptr) {}

DrawTriangleDemo::~DrawTriangleDemo() {}

bool DrawTriangleDemo::LoadContent() {
	return true;
}

void DrawTriangleDemo::UnloadContent() {

	// Release the component
	if (triangleVertexShader_) triangleVertexShader_->Release();
	if (trianglePixelShader_) trianglePixelShader_->Release();
	if (triangleInputLayout_) triangleInputLayout_->Release();
	if (triangleBuffer_) triangleBuffer_->Release();
	
	// Reset all the pointer variable
	triangleVertexShader_ = nullptr;
	trianglePixelShader_ = nullptr;
	triangleInputLayout_ = nullptr;
	triangleBuffer_ = nullptr;
}

void DrawTriangleDemo::Update(float DeltaTime) {}

void DrawTriangleDemo::Render() {}