/*
 * Subdivision.cpp: A class for drawing a Subdivision.
 *
 * Alex Rose
 */


#include "Subdivision.h"
#include "libtarga.h"

#include <stdio.h>
#include <GL/glu.h>

 // Destructor
Subdivision::~Subdivision(void)
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
Subdivision::Initialize(float x, float y, float z, float w)
{
	x_base = x;
	y_base = y;
	z_base = z;
	width = w;
	height = w;
	
	// Now do the geometry. Create the display list.
	display_list = glGenLists(1);

	vector<vector<float>> verts;
	vector<float> v1 = { -.5f * width, 0.5f * width, 0 };
	vector<float> v2 = { -.5f * width, -0.5f * width, 0 };
	vector<float> v3 = { 0, 0, 1 * width };
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));
	
	verts.clear();
	v1 = { 0, 0, 1 * width };
	v2 = { -.5f * width, -.5f * width, 0.0f };
	v3 = { 0.5f * width, -.5f * width, 0.0f };
	
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));

	verts.clear();
	v1 = { .5f * width, .5f * width, 0.0f };
	v2 = { -0.5f * width, .5f * width, 0.0f };
	v3 = { 0, 0, 1 * width };
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));

	verts.clear();
	v1 = { 0, 0, 1 * width };
	v2 = { .5f * width, -.5f * width, 0.0f };
	v3 = { 0.5f * width, .5f * width, 0.0f };
	
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));

	verts.clear();
	
	
	v1 = { 0, 0, -1 * width };
	v2 = { -.5f * width, -0.5f * width, 0 };
	v3 = { -.5f * width, 0.5f * width, 0 };
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));

	verts.clear();
	v3 = { 0, 0, -1 * width };
	v2 = { -.5f * width, -.5f * width, 0.0f };
	v1 = { 0.5f * width, -.5f * width, 0.0f };

	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));

	verts.clear();
	v3 = { .5f * width, .5f * width, 0.0f };
	v2 = { -0.5f * width, .5f * width, 0.0f };
	v1 = { 0, 0, -1 * width };
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));

	verts.clear();
	v3 = { 0, 0, -1 * width };
	v2 = { .5f * width, -.5f * width, 0.0f };
	v1 = { 0.5f * width, .5f * width, 0.0f };

	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	m_triangles.push_back(Triangle(verts));

	m_subdivisionList.push_back(m_triangles);
	m_subdivisionLevel = 0;

	RecreateList();

	// We only do all this stuff once, when the GL context is first set up.
	initialized = true;

	return true;
}


// Draw just calls the display list we set up earlier.
void Subdivision::Draw(void)
{
	glPushMatrix();
	glTranslatef(x_base, y_base, z_base);
	glCallList(display_list);
	glPopMatrix();
}

// Subdivide the Subdivision!
void Subdivision::Subdivide() 
{
	if (m_subdivisionLevel != m_subdivisionList.size() - 1)
	{
		m_subdivisionLevel++;
		m_triangles = m_subdivisionList[m_subdivisionLevel];
		RecreateList();
		return;
	}

	vector<Triangle> new_Triangles;

	for (int i = 0; i < m_triangles.size(); i++)
	{
		vector<Triangle> Triangles = SubdivideTriangle(m_triangles[i]);

		for (int j = 0; j < 4; j++)
		{
			new_Triangles.push_back(Triangles[j]);
		}
	}
	m_subdivisionList.push_back(new_Triangles);
	m_subdivisionLevel++;
	m_triangles = m_subdivisionList[m_subdivisionLevel];

	RecreateList();
}

void Subdivision::RecreateList()
{
	glNewList(display_list, GL_COMPILE);

	for (int i = 0; i < m_triangles.size(); i++)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(m_triangles[i].get_normal()[0],
			m_triangles[i].get_normal()[1],
			m_triangles[i].get_normal()[2]);
		glVertex3f(m_triangles[i].get_vertices()[0][0],
			m_triangles[i].get_vertices()[0][1],
			m_triangles[i].get_vertices()[0][2]);

		glVertex3f(m_triangles[i].get_vertices()[1][0],
			m_triangles[i].get_vertices()[1][1],
			m_triangles[i].get_vertices()[1][2]);

		glVertex3f(m_triangles[i].get_vertices()[2][0],
			m_triangles[i].get_vertices()[2][1],
			m_triangles[i].get_vertices()[2][2]);
		glEnd();
	}

	glEndList();

}

void Subdivision::Unsubdivide()
{
	if (m_subdivisionLevel == 0)
		return;

	m_subdivisionLevel--;
	m_triangles = m_subdivisionList[m_subdivisionLevel];
	RecreateList();
}

vector<Triangle> Subdivision::SubdivideTriangle(Triangle t)
{
	float mag;

	vector<Triangle> dividedTriangles;

	vector<float> p1 = t.get_vertices()[0];
	vector<float> p2 = t.get_vertices()[1];
	vector<float> p3 = t.get_vertices()[2];
	
	vector<float> midpoint1 = { (p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2, (p1[2] + p2[2]) / 2 };
	vector<float> midpoint2 = { (p2[0] + p3[0]) / 2, (p2[1] + p3[1]) / 2, (p2[2] + p3[2]) / 2 };
	vector<float> midpoint3 = { (p1[0] + p3[0]) / 2, (p1[1] + p3[1]) / 2, (p1[2] + p3[2]) / 2 };
	
	mag = sqrt(midpoint1[0] * midpoint1[0] + midpoint1[1] * midpoint1[1] + midpoint1[2] * midpoint1[2]);

	midpoint1[0] = midpoint1[0] / mag * width;
	midpoint1[1] = midpoint1[1] / mag * width;
	midpoint1[2] = midpoint1[2] / mag * width;

	mag = sqrt(midpoint2[0] * midpoint2[0] + midpoint2[1] * midpoint2[1] + midpoint2[2] * midpoint2[2]);

	midpoint2[0] = midpoint2[0] / mag * width;
	midpoint2[1] = midpoint2[1] / mag * width;
	midpoint2[2] = midpoint2[2] / mag * width;

	mag = sqrt(midpoint3[0] * midpoint3[0] + midpoint3[1] * midpoint3[1] + midpoint3[2] * midpoint3[2]);

	midpoint3[0] = midpoint3[0] / mag * width;
	midpoint3[1] = midpoint3[1] / mag * width;
	midpoint3[2] = midpoint3[2] / mag * width;

	dividedTriangles.push_back(Triangle({ p1, midpoint1, midpoint3 }));
	dividedTriangles.push_back(Triangle({ midpoint1, p2, midpoint2 }));
	dividedTriangles.push_back(Triangle({ midpoint3, midpoint2, p3 }));
	dividedTriangles.push_back(Triangle({ midpoint1, midpoint2, midpoint3 }));
	
	return dividedTriangles;
	
}
