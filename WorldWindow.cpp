/*
 * CS559 Maze Project
 *
 * Class file for the WorldWindow class.
 *
 * (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
 *
 */

#include "WorldWindow.h"
#include <Fl/math.h>
#include <Fl/gl.h>
#include <GL/glu.h>
#include <stdio.h>

const double WorldWindow::FOV_X = 45.0;

WorldWindow::WorldWindow(int x, int y, int width, int height, char* label)
	: Fl_Gl_Window(x, y, width, height, label)
{
	button = -1;
	followTrain = false;

	// Initial viewing parameters.
	phi = 45.0f;
	theta = 0.0f;
	dist = 50.0f;
	x_at = 0.0f;
	y_at = 0.0f;
	z_at = 10.0f;
}

void WorldWindow::draw(void)
{
    double  eye[3];
    float   color[4], dir[4];

    if ( ! valid() )
    {
	// Stuff in here doesn't change from frame to frame, and does not
	// rely on any coordinate system. It only has to be done if the
	// GL context is damaged.

	double	fov_y;

	// Sets the clear color to sky blue.
	glClearColor(0.53f, 0.81f, 0.92f, 1.0);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Turn on back face culling. Faces with normals away from the viewer
	// will not be drawn.
	glEnable(GL_CULL_FACE);

	// Enable lighting with one light.
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// Ambient and diffuse lighting track the current color.
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Turn on normal vector normalization. You don't have to give unit
	// normal vector, and you can scale objects.
	glEnable(GL_NORMALIZE);

	// Set up the viewport.
	glViewport(0, 0, w(), h());

	// Set up the persepctive transformation.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fov_y = 360.0f / M_PI * atan(h() * tan(FOV_X * M_PI / 360.0) / w());
	gluPerspective(fov_y, w() / (float)h(), 1.0, 1000.0);

	// Do some light stuff. Diffuse color, and zero specular color
	// turns off specular lighting.
	color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);

	// Initialize all the objects.
	ground.Initialize();
	traintrack.Initialize();
	pyramid.Initialize(0.0, 30, 0, 15, 15);
	pyramid2.Initialize(-15, 30, 0, 7.5, 7.5);
	pyramid3.Initialize(15, 30, 0, 12.5, 12.5);
	tree.Initialize(-25, 0, 0, 1, 5);
	tree2.Initialize(-22.5, 0, 0, 1.2, 6);
	tree3.Initialize(-27.5, 0, 0, .75, 4);
	ride.Initialize(30, -10, 0, 10);
	ride2.Initialize(30, -40, 0, 18);
	ride3.Initialize(10, -20, 0, 24);
	sub.Initialize(0, 0, 8, 8);
	sub2.Initialize(-15, 15, 15, 15);
    }

    // Stuff out here relies on a coordinate system or must be done on every
    // frame.

    // Clear the screen. Color and depth.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Set up the viewing transformation. The viewer is at a distance
    // dist from (x_at, y_ay, 2.0) in the direction (theta, phi) defined
    // by two angles. They are looking at (x_at, y_ay, 2.0) and z is up.
    eye[0] = x_at + dist * cos(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
    eye[1] = y_at + dist * sin(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
    eye[2] = z_at + dist * sin(phi * M_PI / 180.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, z_at, 0.0, 0.0, 1.0);

    // Position the light source. This has to happen after the viewing
    // transformation is set up, so that the light stays fixed in world
    // space. This is a directional light - note the 0 in the w component.
    dir[0] = 1.0; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, dir);

    // Draw stuff. Everything.
    ground.Draw();
    traintrack.Draw();
	pyramid.Draw();
	pyramid2.Draw();
	pyramid3.Draw();
	tree.Draw();
	tree2.Draw();
	tree3.Draw();
	ride.Draw();
	ride2.Draw();
	ride3.Draw();
	sub.Draw();
	sub2.Draw();
}

void WorldWindow::Move(float dt)
{
	switch (key)
	{
	case 'w':
		x_at += 0.5;
		break;
	case 's':
		x_at -= 0.5;
		break;
	case 'a':
		y_at += 0.5;
		break;
	case 'd':
		y_at -= 0.5;
		break;
	case 'q':
		z_at += 0.5;
		break;
	case 'e':
		z_at -= 0.5;
		break;
	}
}

void
WorldWindow::Drag(float dt)
{
    int	    dx = x_down - x_last;
    int     dy = y_down - y_last;

    switch ( button )
    {
      case FL_LEFT_MOUSE:
	// Left button changes the direction the viewer is looking from.
	theta = theta_down + 360.0f * dx / (float)w();
	while ( theta >= 360.0f )
	    theta -= 360.0f;
	while ( theta < 0.0f )
	    theta += 360.0f;
	phi = phi_down + 90.0f * dy / (float)h();
	if ( phi > 89.0f )
	    phi = 89.0f;
	if ( phi < -5.0f )
	    phi = -5.0f;
	break;
      case FL_MIDDLE_MOUSE:
	// Middle button moves the viewer in or out.
	dist = dist_down - ( 0.5f * dist_down * dy / (float)h() );
	if ( dist < 1.0f )
	    dist = 1.0f;
	break;
      case FL_RIGHT_MOUSE: {
	// Right mouse button moves the look-at point around, so the world
	// appears to move under the viewer.
	float	x_axis[2];
	float	y_axis[2];

	x_axis[0] = -(float)sin(theta * M_PI / 180.0);
	x_axis[1] = (float)cos(theta * M_PI / 180.0);
	y_axis[0] = x_axis[1];
	y_axis[1] = -x_axis[0];

	x_at = x_at_down + 100.0f * ( x_axis[0] * dx / (float)w()
				    + y_axis[0] * dy / (float)h() );
	y_at = y_at_down + 100.0f * ( x_axis[1] * dx / (float)w()
				    + y_axis[1] * dy / (float)h() );
	} break;
      default:;
    }
}


bool
WorldWindow::Update(float dt)
{
    // Update the view. This gets called once per frame before doing the
    // drawing.

    if ( button != -1 ) // Only do anything if the mouse button is down.
	Drag(dt);

	if (key == 'w' ||
		key == 'a' ||
		key == 's' ||
		key == 'd' ||
		key == 'q' ||
		key == 'e')
	{
		Move(dt);
	}
	
	else if (key == FL_Escape)
	{

	}

	if (followTrain)
	{
		float* posn = traintrack.get_posn();

		x_at = posn[0];
		y_at = posn[1];
		z_at = posn[2];
	}

    // Animate the train.
    traintrack.Update(dt);

	//Animate the rides.
	ride.Update(dt);
	ride2.Update(dt);
	ride3.Update(dt);


    return true;
}


int
WorldWindow::handle(int event)
{
    // Event handling routine. Only looks at mouse events.
    // Stores a bunch of values when the mouse goes down and keeps track
    // of where the mouse is and what mouse button is down, if any.
    switch ( event )
    {
	case FL_KEYDOWN:
		if (Fl::event_key() != FL_Escape)
		{
			key = Fl::event_key();
			return 1;
		}
		
		break;
	case FL_KEYUP:
		if (Fl::event_key() == '1')
		{
			if (!followTrain)
				followTrain = true;
			else
				followTrain = false;
		}
		else if (Fl::event_key() == '2')
		{
			sub.Subdivide();
			sub2.Subdivide();
		}
		else if (Fl::event_key() == '3')
		{
			sub.Unsubdivide();
			sub2.Unsubdivide();
		}
		key = 0;
		break;
      case FL_PUSH:
        button = Fl::event_button();
		x_last = x_down = Fl::event_x();
		y_last = y_down = Fl::event_y();
		phi_down = phi;
		theta_down = theta;
		dist_down = dist;
		x_at_down = x_at;
		y_at_down = y_at;
		return 1;
      case FL_DRAG:
	x_last = Fl::event_x();
	y_last = Fl::event_y();
	return 1;
      case FL_RELEASE:
        button = -1;
	return 1;
    }

    // Pass any other event types on the superclass.
    return Fl_Gl_Window::handle(event);
}


