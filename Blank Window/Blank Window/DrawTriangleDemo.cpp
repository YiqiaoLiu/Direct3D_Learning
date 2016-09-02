#include "DrawTriangleDemo.h"
#include <xnamath.h>


// The vertex's struct
struct VertexPostion
{
	XMFLOAT3 vertexPos;
};

DrawTriangleDemo::DrawTriangleDemo() : triangleVertexShader_(nullptr), trianglePixelShader_(nullptr), triangleInputLayout_(nullptr), triangleBuffer_(nullptr) {}

DrawTriangleDemo::~DrawTriangleDemo() {}

bool DrawTriangleDemo::LoadContent() {
	// First, load the Vertex Shader
	// Allocate memory space for vertex shader and error buffer
	ID3DBlob* vsBuffer = nullptr;
	ID3DBlob* errBuffer = nullptr;

	// Compile shader from file
	DWORD shaderFlag = D3DCOMPILE_DEBUG;
	HRESULT vsCompileResult;
	vsCompileResult = D3DX11CompileFromFile("SolidRedColor.fx", 0, 0, "VS_Main", "vs_4_0", shaderFlag, 0, 0, &vsBuffer, &errBuffer, 0);

	// If create failed output the error log and return false
	if (FAILED(vsCompileResult)) {
		if (errBuffer != NULL) {
			OutputDebugStringA((char*)errBuffer->GetBufferPointer());
			errBuffer->Release();
		}
		return false;
	}

	// Create the Vertex Shader
	HRESULT vsCreateResult;
	vsCreateResult = d3dDevice_->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), 0, &triangleVertexShader_);

	// If create failed out put the log and return false
	if (FAILED(vsCreateResult)) {
		MessageBox(0, "Failed to create the vertex shader", 0, MB_OK);
		vsBuffer->Release();
		return false;
	}
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