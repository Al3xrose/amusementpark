/*
 * Ride.cpp: A class for drawing a Ride.
 *
 * Alex Rose
 */


#include "Ride.h"
#include "libtarga.h"

#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>

 // Destructor
Ride::~Ride(void)
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
Ride::Initialize(float x, float y, float z, float w)
{
	x_base = x;
	y_base = y;
	z_base = z;
	width = w;
	scale = w / 10.0f;

	ubyte* image_data;
	int	    image_height, image_width;

	GLfloat xRotated, yRotated, zRotated;
	rotAngle = 0.0f;
	rotAngle2 = 0.0f;

	//int height, width, nrChannels;

	//unsigned char* data = stbi_load("chesterfieldsofa_metallic.png", &width, &image_height, &nrChannels, 0 );

	// Load the image for the texture. The texture file has to be in
	// a place where it will be found.
	if (!(image_data = (ubyte*)tga_load("Untitled.tga", &image_width,
		&image_height, TGA_TRUECOLOR_24)))
	{
		fprintf(stderr, "Ride::Initialize: Couldn't load grass.tga\n");
		return false;
	}

	/*
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
	*/

	//glutSolidCone(base, height, slices, stacks);
	// Flush buffers to screen

	//glFlush();
	// sawp buffers called because we are using double buffering 
    // glutSwapBuffers();
	//glDisable(GL_TEXTURE_2D);
	//glEndList();

	// We only do all this stuff once, when the GL context is first set up.
	initialized = true;

	return true;
}

void Ride::Update(float dt)
{
	rotAngle += dt * 50;
	if (rotAngle > 360)
		rotAngle = 0.0f;

	rotAngle2 += dt * 100;
	if (rotAngle2 > 360)
		rotAngle2 = 0.0f;
}


// Draw just calls the display list we set up earlier.
void Ride::Draw(void)
{
	GLUquadric* q = gluNewQuadric();
	gluQuadricDrawStyle(q, GLU_FILL);

	glPushMatrix();

	glTranslatef(x_base, y_base, z_base);
	glTranslatef(0, 0, .5f * scale);
	glColor3f(0.45, .24, .19);
	glutSolidCube(2.0f * scale );
	
	glPushMatrix();

	glColor3f(.65, .21, .25);
	glRotatef(rotAngle, 0, 0, 1);
	glTranslatef(-(width/2.0f), 0, 1.25 * scale);
	glRotatef(90, 0, 1, 0);
	gluCylinder(q, .5 * scale, .5 * scale, width, 10, 10);

	glPushMatrix();
	
	glColor3f(.17, .37, .45);
	glutSolidCube(1.0f * scale);
	
	glPushMatrix();
	
	glRotatef(-rotAngle2, 1, 0, 0);
	glTranslatef(-1.0f * scale, 0, -2.0f * scale);
	gluCylinder(q, 0.25 * scale, 0.25 * scale, 4.0f * scale, 10, 10);
	
	glColor3f(.75, .75, .75);
	glutSolidCube(.75f * scale);
	
	glPushMatrix();
	glTranslatef(0, 0, 4.0f * scale);
	glutSolidCube(.75f * scale);
	glPopMatrix();

	glPopMatrix();
	
	glPopMatrix();
	
	glPushMatrix();
	
	glTranslatef(0, 0, 10.0f * scale);
	glColor3f(.17, .37, .45);
	glutSolidCube(1.0 * scale);

	glPushMatrix();

	glRotatef(-rotAngle2, 1, 0, 0);
	glTranslatef(-1 * scale, 0, -2 * scale);
	gluCylinder(q, .25 * scale, .25 * scale, 4.0f * scale, 10.0f * scale, 10.0f * scale);
	glColor3f(.75, .75, .75);
	glutSolidCube(.75 * scale);

	glPushMatrix();

	glTranslatef(0, 0, 4 * scale);
	glutSolidCube(.75f * scale);
	
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	gluDeleteQuadric(q);
}