#pragma once

#ifndef _BASE_DX11_H_
#define _BASE_DX11_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <DxErr.h>

// The base object of the demo
class BaseDx11
{
public:

	BaseDx11();										// Constructor of class
	virtual ~BaseDx11();							// Destruct of the class
	virtual bool LoadContent();						// Load content to the window
	virtual void UnloadContent();					// Unload content in the window
	virtual void Update(float DeltaTime);			// Update the content of the window each DeltaTime interval
	virtual void Render();							// Render the window
	void InitializeSetting(HWND hwnd);				// Initialize the d3d window setting
	void CloseWindow();								// Close the window

protected:

	ID3D11RenderTargetView* backBufferTarget_;		// The variable store the back buffer
	ID3D11DeviceContext* d3dDeviceContext_;			// The variable store the d3d context
	ID3D11Device* d3dDevice_;						// The variable store the d3d device
	IDXGISwapChain* swapChain_;						// The variable store the d3d swap chain

	D3D_DRIVER_TYPE driverType_;					// The driver of the d3d
	D3D_FEATURE_LEVEL featureLevel_;				// The feature level of the d3d


private:
};
#endif