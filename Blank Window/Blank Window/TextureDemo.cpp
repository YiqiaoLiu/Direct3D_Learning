#include "TextureDemo.h"
#include <xnamath.h>

struct VertexInfo 
{
	XMFLOAT3 postion;
	XMFLOAT2 texture;
};

TextureDemo::TextureDemo() :textureVertexShader_(nullptr), texturePixelShader_(nullptr), textureInputLayout_(nullptr), textureVertexBuffer_(nullptr),
							colorMap_(nullptr), colorMapSampler_(nullptr) {}

TextureDemo::~TextureDemo() {}

bool TextureDemo::LoadContent() {
	//////////////////////////////////////////////////////////
	//           First, load the Vertex Shader              //
	//////////////////////////////////////////////////////////

	// Set the memory space for vertex shader buffer and error buffer
	ID3DBlob* vsBuffer = nullptr;
	ID3DBlob* errBuffer = nullptr;

	// Compile the shader from file
	DWORD shaderFlag = D3DCOMPILE_DEBUG;
	HRESULT vsCompileResult;
	vsCompileResult = D3DX11CompileFromFile("Texture.fx", 0, 0, "VS_Main", "vs_4_0", shaderFlag, 0, 0, &vsBuffer, &errBuffer, 0);

	// If compile failed, output the err log and return
	if (FAILED(vsCompileResult)) {
		if (!errBuffer) {
			OutputDebugStringA((char*)errBuffer->GetBufferPointer());
			errBuffer->Release();
		}
		return false;
	}

	// Create the vertex shader
	HRESULT vsCreateResult;
	vsCreateResult = d3dDevice_->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), 0, &textureVertexShader_);
	if (FAILED(vsCreateResult)) {
		MessageBox(0, "Failed to create the vertex shader", 0, MB_OK);
		if (vsBuffer) vsBuffer->Release();
		return false;
	}

	//////////////////////////////////////////////////////////
	//           Second, load the input layer               //
	//////////////////////////////////////////////////////////
	
	// Create the input layout description
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	int totalInputLayout = ARRAYSIZE(inputLayoutDesc);
	HRESULT inputLayoutCreateResult;
	inputLayoutCreateResult = d3dDevice_->CreateInputLayout(inputLayoutDesc, totalInputLayout, vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &textureInputLayout_);

	// If create failed, output the error log and return false
	if (FAILED(inputLayoutCreateResult)) {
		MessageBox(0, "Failed to create the input layout!", 0, MB_OK);
		return false;
	}

	// Release the vertex buffer
	if (vsBuffer) vsBuffer->Release();

	//////////////////////////////////////////////////////////
	//           Third, load the Pixel Shader               //
	//////////////////////////////////////////////////////////

	// Allocate the memory space for the pixel buffer and the error buffer
	ID3DBlob* psBuffer = nullptr;
	ID3DBlob* psErrBuffer = nullptr;

	// Compile the pixel shader from the file
	HRESULT psCompileResult;
	psCompileResult = D3DX11CompileFromFile("Texture.fx", 0, 0, "PS_Main", "ps_4_0", shaderFlag, 0, 0, &psBuffer, &psErrBuffer, 0);

	// If failed, output the error log and return
	if (FAILED(psCompileResult)) {
		if (psErrBuffer) {
			OutputDebugStringA((char*)psErrBuffer->GetBufferPointer());
			psErrBuffer->Release();
		}
		return false;
	}

	// Create the pixel shader
	HRESULT psCreateResult;
	psCreateResult = d3dDevice_->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), 0, &texturePixelShader_);

	// If failed to create, output the error log and return false
	if (FAILED(psCreateResult)) {
		MessageBox(0, "Failed create the pixel shader!", 0, MB_OK);
		if (psBuffer) psBuffer->Release();
		return false;
	}

	if (psBuffer) psBuffer->Release();

	//////////////////////////////////////////////////////////
	//              Finally, Load the geometry              //
	//////////////////////////////////////////////////////////

	// First, define the vertex
	VertexInfo vertices[] = {
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
	};

	// Create the vertex buffer description
	D3D11_BUFFER_DESC vertextBufferDesc;
	ZeroMemory(&vertextBufferDesc, sizeof(vertextBufferDesc));
	vertextBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertextBufferDesc.ByteWidth = sizeof(VertexInfo) * 6;
	vertextBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// Create the sub-resource
	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(subResource));
	subResource.pSysMem = vertices;

	// Create the vertex buffer
	HRESULT vbCreateResult;
	vbCreateResult = d3dDevice_->CreateBuffer(&vertextBufferDesc, &subResource, &textureVertexBuffer_);
	if (FAILED(vbCreateResult)) {
		MessageBox(0, "Failed to create the vertex buffer", 0, MB_OK);
		return false;
	}

	return true;

}

void TextureDemo::UnloadContent() {
	
	// First, delete all the resource by using release function
	if (textureVertexShader_) textureVertexShader_->Release();
	if (texturePixelShader_) texturePixelShader_->Release();
	if (textureInputLayout_) textureInputLayout_->Release();
	if (textureVertexBuffer_) textureVertexBuffer_->Release();
	if (colorMap_) colorMap_->Release();
	if (colorMapSampler_) colorMapSampler_->Release();

	// Second, reset all the resource
	textureVertexShader_ = nullptr;
	texturePixelShader_ = nullptr;
	textureInputLayout_ = nullptr;
	textureVertexBuffer_ = nullptr;
	colorMap_ = nullptr;
	colorMapSampler_ = nullptr;

}

void TextureDemo::Render() {}

void TextureDemo::Update(float DeltaTime) {}