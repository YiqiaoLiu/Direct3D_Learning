#pragma once

#ifndef __DRAW_TRIANGLE_DEMO__H
#define __DRAW_TRIANGLE_DEMO__H

#include "BaseDx11.h"

class DrawTriangleDemo : public BaseDx11 {

public:
	DrawTriangleDemo();									// The constructor of the class
	virtual ~DrawTriangleDemo();						// The destructor of the class
	bool LoadContent();									// Load the content to the window
	void UnloadContent();								// Unload the content in the window
	void Update(float DeltaTime);						// Update the content in the window
	void Render();										// Render the content in the window

protected:
	ID3D11VertexShader* triangleVertexShader_;			// The vertex shader of the triangle
	ID3D11PixelShader* trianglePixelShader_;			// The pixel shader of the triangle
	ID3D11InputLayout* triangleInputLayout_;			// The input layout of the triangle
	ID3D11Buffer* triangleBuffer_;						// The buffer(vertex buffer) of the triangle
};
#endif