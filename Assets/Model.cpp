/*
 * Model.cpp
 *
 *  Created on: May 5, 2019
 *      Author: Joseph Haske
 */

#include "Model.h"

Model::Model() {
	v = new Vertex[MAX_VERTICES];
	t = new Triangle[MAX_TRIANGLES];
	m = new Material[MAX_MATERIALS];

	numVertices = 0;
	numTriangles = 0;
	numMaterials = 0;
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void Model::addVertex(Vec3D<GLfloat> vec)
{
	v[numVertices++].coord = vec;
}

void Model::addTriangle(Vec3D<int> vec)
{
	t[numTriangles++].vert = vec;
	t[numTriangles].m = t[numTriangles-1].m;
}

void Model::addMaterial(std::string n)
{
	m[numMaterials++].matName = n;
}
void Model::matSetEmission(Vec4D<GLfloat> e)
{
	m[numMaterials-1].emission = e;
}
void Model::matSetAmbient(Vec4D<GLfloat> a)
{
	m[numMaterials-1].ambient = a;
}
void Model::matSetDiffuse(Vec4D<GLfloat> d)
{
	m[numMaterials-1].diffuse = d;
}
void Model::matSetSpecular(Vec4D<GLfloat> s)
{
	m[numMaterials-1].specular = s;
}
void Model::setTriangleMaterial(std::string name)
{
	getMaterial(name, t[numTriangles].m);
}

void Model::getMaterial(std::string name, Material *&mat)
{
	for(int i=0; i<numMaterials; i++)
	{
		if(name == m[i].matName)
		{
			mat = &m[i];
		}
	}
}

/**
 * Draws the current model.
 */
void Model::drawModel()
{
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < numTriangles; i++)
    {
	    glColor3f(t[i].m->specular.getW(), t[i].m->specular.getX(), t[i].m->specular.getY());

    	glVertex3f(v[t[i].vert.getX()].coord.getX(), v[t[i].vert.getX()].coord.getY(), v[t[i].vert.getX()].coord.getZ());
    	glVertex3f(v[t[i].vert.getY()].coord.getX(), v[t[i].vert.getY()].coord.getY(), v[t[i].vert.getY()].coord.getZ());
    	glVertex3f(v[t[i].vert.getZ()].coord.getX(), v[t[i].vert.getZ()].coord.getY(), v[t[i].vert.getZ()].coord.getZ());
    }
    glEnd();
	//std::cout << "GOT HERE\n";
}

/**
 * Prints the model data for debugging.
 */
void Model::printModel()
{
	std::cout << "Number of Vertices: " << numVertices << '\n';
	std::cout << "Number of Triangles: " << numTriangles << '\n';
	std::cout << "Number of Materials: " << numMaterials << '\n';
}
