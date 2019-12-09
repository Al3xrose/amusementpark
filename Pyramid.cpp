/*
 * Pyramid.cpp: A class for drawing a pyramid.
 *
 * Alex Rose
 */


#include "Pyramid.h"
#include "libtarga.h"

#include <stdio.h>
#include <GL/glu.h>

 // Destructor
Pyramid::~Pyramid(void)
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
Pyramid::Initialize(float x, float y, float z, float w, float h)
{
	x_base = x;
	y_base = y;
	z_base = z;
	height = h;
	width = w;

	ubyte* image_data;
	int	    image_height, image_width;

	//int height, width, nrChannels;

	//unsigned char* data = stbi_load("chesterfieldsofa_metallic.png", &width, &image_height, &nrChannels, 0 );

	// Load the image for the texture. The texture file has to be in
	// a place where it will be found.
	if (!(image_data = (ubyte*)tga_load("Untitled.tga", &image_width,
		&image_height, TGA_TRUECOLOR_24)))
	{
		fprintf(stderr, "Pyramid::Initialize: Couldn't load grass.tga\n");
		return false;
	}

	// This creates a texture object and binds it, so the next few operations
	// apply to this texture.
	glGenTextures(1, &texture_obj);
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	// This sets a parameter for how the texture is loaded and interpreted.
	// basically, it says that the data is packed tightly in the image array.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// This sets up the texture with high quality filtering. First it builds
	// mipmaps from the image data, then it sets the filtering parameters
	// and the wrapping parameters. We want the grass to be repeated over the
	// Pyramid.
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_width, image_height,
		GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST_MIPMAP_LINEAR);

	// This says what to do with the texture. Modulate will multiply the
	// texture by the underlying color.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Now do the geometry. Create the display list.
	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);

	// Turn on texturing and bind the grass texture.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	// Draw the base of the Pyramid as a quadrilateral, specifying texture coordinates.
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0, 0, -1);
	
	glTexCoord2f(-1.0, -1.0);
	glVertex3f(x_base - width/2, y_base - width/2, z_base);
	glTexCoord2f(-1.0, 1.0);
	glVertex3f(x_base - width / 2, y_base + width / 2, z_base);
	glTexCoord2f(1, 1);
	glVertex3f(x_base + width / 2, y_base + width / 2, z_base);
	glTexCoord2f(1.0, -1.0);
	glVertex3f(x_base + width / 2, y_base - width / 2, z_base);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(-1.0, 0.0, 1.0);
	glTexCoord2f(1, 0);
	glVertex3f(x_base - width / 2.0, y_base + width / 2.0, z_base);
	glTexCoord2f(0, 0);
	glVertex3f(x_base - width / 2.0, y_base - width / 2.0, z_base);
	glTexCoord2f(.5, 1);
	glVertex3f(x_base, y_base, z_base + height);
	
	
	glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, -1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(.5, 1);
	glVertex3f(x_base, y_base, z_base + height);
	glTexCoord2f(0, 0);
	glVertex3f(x_base - width / 2.0, y_base - width / 2.0, z_base);
	glTexCoord2f(1, 0);
	glVertex3f(x_base + width / 2.0, y_base - width / 2.0, z_base);
	glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(1, 0);
	glVertex3f(x_base + width / 2.0, y_base + width / 2.0, z_base);
	glTexCoord2f(0, 0);
	glVertex3f(x_base - width / 2.0, y_base + width / 2.0, z_base);
	glTexCoord2f(.5, 1);
	glVertex3f(x_base, y_base, z_base + height);
	
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(1.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(.5, 1);
	glVertex3f(x_base, y_base, z_base + height);
	glTexCoord2f(0, 0);
	glVertex3f(x_base + width / 2.0, y_base - width / 2.0, z_base);
	glTexCoord2f(1, 0);
	glVertex3f(x_base + width / 2.0, y_base + width / 2.0, z_base);
	glEnd();
	// Turn texturing off again, because we don't want everything else to
	// be textured.
	glDisable(GL_TEXTURE_2D);
	glEndList();

	// We only do all this stuff once, when the GL context is first set up.
	initialized = true;

	return true;
}


// Draw just calls the display list we set up earlier.
void Pyramid::Draw(void)
{
	glPushMatrix();
	glCallList(display_list);
	glPopMatrix();
}