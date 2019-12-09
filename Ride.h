/*
 * Ride.h: Header file for a class that draws a Ride.
 *
 * Alex Rose
 *
 */

#ifndef _Ride_H_
#define _Ride_H_

#include <Fl/gl.h>

class Ride {
private:
	GLubyte display_list;   // The display list that does all the work.
	GLuint  texture_obj;    // The object for the Ride texture.
	bool    initialized;    // Whether or not we have been initialised.
	float x_base;
	float y_base;
	float z_base;
	float v_step;
	float width;
	float scale;
	GLdouble base;
	GLdouble height;
	GLint slices = 100;
	GLint stacks = 100;
	GLfloat rotAngle;
	GLfloat rotAngle2;

public:
	// Constructor. Can't do initialization here because we are
	// created before the OpenGL context is set up.
	Ride(void) { display_list = 0; initialized = false; };

	// Destructor. Frees the display lists and texture object.
	~Ride(void);

	// Initializer. Creates the display list.
	bool    Initialize(float x, float y, float z, float w);

	// Does the drawing.
	void    Draw(void);

	//Update rotations
	void Update(float dt);
};


#endif
