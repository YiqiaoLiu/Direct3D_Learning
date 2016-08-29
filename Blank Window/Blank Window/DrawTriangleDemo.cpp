#include "DrawTriangleDemo.h"

DrawTriangleDemo::DrawTriangleDemo() : triangleVertexShader_(nullptr), trianglePixelShader_(nullptr), triangleInputLayout_(nullptr), triangleBuffer_(nullptr) {}

DrawTriangleDemo::~DrawTriangleDemo() {}

bool DrawTriangleDemo::LoadContent() {
	return true;
}

void DrawTriangleDemo::UnloadContent() {}

void DrawTriangleDemo::Update(float DeltaTime) {}

void DrawTriangleDemo::Render() {}