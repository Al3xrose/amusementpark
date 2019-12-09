/*
 * Tree.cpp: A class for drawing a Tree.
 *
 * Alex Rose
 */


#include "Tree.h"
#include "libtarga.h"

#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>

 // Destructor
Tree::~Tree(void)
{
	if (initialized)
	{
		glDeleteLists(display_list, 1);
		glDeleteTextures(1, &texture_obj);
	}
}


// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Tree::Initialize(float x, float y, float z, float w, float h)
{
	x_base = x;
	y_base = y;
	z_base = z;
	//height = h;
	width = w;
	height = h;

	ubyte* image_data;
	int	    image_height, image_width;

	GLfloat xRotated, yRotated, zRotated;
	

	//int height, width, nrChannels;

	//unsigned char* data = stbi_load("chesterfieldsofa_metallic.png", &width, &image_height, &nrChannels, 0 );

	// Load the image for the texture. The texture file has to be in
	// a place where it will be found.
	if (!(image_data = (ubyte*)tga_load("Untitled.tga", &image_width,
		&image_height, TGA_TRUECOLOR_24)))
	{
		fprintf(stderr, "Tree::Initialize: Couldn't load grass.tga\n");
		return false;
	}
	
	//glBegin(GL_QUADS);
	//glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	// clear the identity matrix.
	glLoadIdentity();
	// traslate the draw by z = -4.0
	// Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
	glTranslatef(0.0, 0.0, -4.5);
	// Red color used to draw.
	glColor3f(0.8, 0.2, 0.1);
	// changing in transformation matrix.
	// rotation about X axis
	xRotated = yRotated = zRotated = 30.0;
	xRotated = 33;
	yRotated = 40;
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a Cone.


	//glutSolidCone(base, height, slices, stacks);
	// Flush buffers to screen

	glFlush();
	// sawp buffers called because we are using double buffering 
   // glutSwapBuffers();
	//glDisable(GL_TEXTURE_2D);
	//glEndList();

	// We only do all this stuff once, when the GL context is first set up.
	initialized = true;

	return true;
}


// Draw just calls the display list we set up earlier.
void Tree::Draw(void)
{
	
	glPushMatrix();
	glTranslatef(x_base, y_base, z_base);
	glColor3f(0.4, .26, .13);
	GLUquadric *q = gluNewQuadric();
	gluCylinder(q, 0.5, 0.5, 1.0, 10.0, 10.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0, 0, 1);
	glutSolidCone(width, height, slices, stacks);
	glPopMatrix();
	glPopMatrix();
	//glTranslatef(0.0, 0.0, 5.0);
	//glutSolidTeapot(2.0);
	//glutSolidTorus(2.0, 4.0, 5, 10);
	/*glPushMatrix();
	glCallList(display_list);
	glPopMatrix();*/
}