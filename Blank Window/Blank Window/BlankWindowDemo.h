#pragma once

#ifndef __BLANK_WINDOW_DEMO__H
#define __BLANK_WINDOW_DEMO__H

#include "BaseDx11.h"

class BlankWindowDemo: public BaseDx11
{
public:
	BlankWindowDemo();						// The constructor of the class
	virtual ~BlankWindowDemo();				// The destructor of the class
	bool LoadContent();						// Load content to the window
	void UnloadContent();					// Unload content in the window
	void Update(float DeltaTime);			// Update the content in the window
	void Render();							// Render the window
};
#endif