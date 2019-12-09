#include "Triangle.h"
#include <vector>
using namespace std;

Triangle::Triangle(vector<vector<float>> vertices)
{
	m_vertices = vertices;
}

vector<float> Triangle::get_normal()
{
	return { (m_vertices[0][0] + m_vertices[1][0] + m_vertices[2][0]) / 3, 
	         (m_vertices[0][1] + m_vertices[1][1] + m_vertices[2][1]) / 3,
	         (m_vertices[0][2] + m_vertices[1][2] + m_vertices[2][2]) / 3};
}