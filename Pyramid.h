/*
 * Pyramid.h: Header file for a class that draws a pyramid.
 *
 * Alex Rose
 *
 */

#ifndef _PYRAMID_H_
#define _PYRAMID_H_

#include <Fl/gl.h>

class Pyramid {
private:
	GLubyte display_list;   // The display list that does all the work.
	GLuint  texture_obj;    // The object for the pyramid texture.
	bool    initialized;    // Whether or not we have been initialised.
	float x_base;
	float y_base;
	float z_base;
	float height;
	float width;

public:
	// Constructor. Can't do initialization here because we are
	// created before the OpenGL context is set up.
	Pyramid(void) { display_list = 0; initialized = false; };

	// Destructor. Frees the display lists and texture object.
	~Pyramid(void);

	// Initializer. Creates the display list.
	bool    Initialize(float x, float y, float z, float w, float h);

	// Does the drawing.
	void    Draw(void);
};


#endif
