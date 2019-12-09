#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <vector>
using namespace std;

class Triangle {
public: 
	Triangle(vector<vector<float>> vertices);
	vector<vector<float>> get_vertices() { return m_vertices; }
	vector<float> get_normal();

private:
	vector<vector<float>> m_vertices;
};

#endif