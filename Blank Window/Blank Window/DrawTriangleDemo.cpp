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

	// If compile failed output the error log and return false
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

	// Second, load the input layer
	// Create a description of the input layer will be created
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	// Create the input layer
	int totalInputLayout = ARRAYSIZE(inputLayoutDesc);
	HRESULT ilCreateResult;
	ilCreateResult = d3dDevice_->CreateInputLayout(inputLayoutDesc, totalInputLayout, vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &triangleInputLayout_);

	// If create failed, out put the error log and return false
	if (FAILED(ilCreateResult)) {
		MessageBox(0, "Failed to create the input layout", 0, MB_OK);
		return false;
	}

	//  If create layout success, release the vertex buffer
	vsBuffer->Release();
	
	// Third, load the Pixel Shader
	// Allocate memory space for Pixel Shader and error buffer
	ID3DBlob* psBuffer = nullptr;
	ID3DBlob* psErrBuffer = nullptr;

	// Compile shader from file
	HRESULT psCompileResult;
	psCompileResult = D3DX11CompileFromFile("SolidRedColor.fx", 0, 0, "VS_Main", "vs_4_0", shaderFlag, 0, 0, &psBuffer, &psErrBuffer, 0);

	// If compile failed output the error log and return false
	if (FAILED(psCompileResult)) {
		if (psErrBuffer != nullptr) {
			OutputDebugStringA((char*)psErrBuffer->GetBufferPointer());
			psErrBuffer->Release();
		}
		return false;
	}

	// Create the Vertex Shader
	HRESULT psCreateResult;
	psCreateResult = d3dDevice_->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), 0, &trianglePixelShader_);

	// If create failed out put the log and return false
	if (FAILED(psCreateResult)) {
		MessageBox(0, "Failed to create Pixel Shader", 0, MB_OK);
		if (psBuffer != nullptr) psBuffer->Release();
		return false;
	}
	psBuffer->Release();
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