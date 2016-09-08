#include "Texture2D.h"

TextureDemo::TextureDemo() :textureVertexShader_(nullptr), texturePixelShader_(nullptr), textureInputLayout_(nullptr), textureVertexBuffer_(nullptr),
							colorMap_(nullptr), colorMapSampler_(nullptr) {}

TextureDemo::~TextureDemo() {}

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