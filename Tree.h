/*
 * Tree.h: Header file for a class that draws a Tree.
 *
 * Alex Rose
 *
 */

#ifndef _TREE_H_
#define _TREE_H_

#include <Fl/gl.h>

class Tree {
private:
	GLubyte display_list;   // The display list that does all the work.
	GLuint  texture_obj;    // The object for the Tree texture.
	bool    initialized;    // Whether or not we have been initialised.
	float x_base;
	float y_base;
	float z_base;
	//float height;
	float width;
	GLdouble base;
	GLdouble height;
	GLint slices = 100;
	GLint stacks = 100;

public:
	// Constructor. Can't do initialization here because we are
	// created before the OpenGL context is set up.
	Tree(void) { display_list = 0; initialized = false; };

	// Destructor. Frees the display lists and texture object.
	~Tree(void);

	// Initializer. Creates the display list.
	bool    Initialize(float x, float y, float z, float w, float h);

	// Does the drawing.
	void    Draw(void);
};


#endif
