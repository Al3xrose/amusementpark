/*
 * Subdivision.h: Header file for a class that draws a Subdivision.
 *
 * Alex Rose
 *
 */

#ifndef _Subdivision_H_
#define _Subdivision_H_

#include <Fl/gl.h>
#include <vector>
#include "Triangle.h"
using namespace std;

class Subdivision {
private:
	GLubyte display_list;   // The display list that does all the work.
	GLuint  texture_obj;    // The object for the Subdivision texture.
	bool    initialized;    // Whether or not we have been initialised.
	float x_base;
	float y_base;
	float z_base;
	float width;
	float height;
	vector<Triangle> m_triangles;
	vector<vector<Triangle>> m_subdivisionList;
	int m_subdivisionLevel = 0;

public:
	// Constructor. Can't do initialization here because we are
	// created before the OpenGL context is set up.
	Subdivision(void) { display_list = 0; initialized = false; };

	// Destructor. Frees the display lists and texture object.
	~Subdivision(void);

	// Initializer. Creates the display list.
	bool    Initialize(float x, float y, float z, float w);

	// Does the drawing.
	void    Draw(void);

	//Subdivide the subdivision!
	void Subdivide();

	//Subdivide a single Triangle, return 4 triangles!
	vector<Triangle> SubdivideTriangle(Triangle t);

	//Unsubdivide -- reverse the previous subdivision
	void Unsubdivide();

	//Recreate display list when subdivision level changes
	void RecreateList();
};


#endif
