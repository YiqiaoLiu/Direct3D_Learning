#pragma once

#ifndef _TEXTURE_2D_H_
#define _TEXTURE_2D_H_

#include "BaseDx11.h"
class TextureDemo
{
public:
	TextureDemo();											// The constructor of the class
	virtual ~TextureDemo();									// The destructor of the class
	bool LoadContent();										// Load the content to the window
	void UnloadContent();									// Unload the content in the window
	void Update(float DeltaTime);							// Update the content in the window
	void Render();											// Render the content in the window

private:
	ID3D11VertexShader* textureVertexShader_;				// The vertex shader of the texture
	ID3D11PixelShader* texturePixelShader_;					// The pixel shader of the texture
	ID3D11InputLayout* textureInputLayout_;					// The input layout of the texture
	ID3D11Buffer* textureVertexBuffer_;						// The vertex buffer of the texture
	ID3D11ShaderResourceView* colorMap_;					// The shader resource view get data by shader
	ID3D11SamplerState* colorMapSampler_;					// The sampler
};

#endif // !_TEXTURE_2D_H_

