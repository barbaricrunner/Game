/*
 * ModelHandler.h
 *
 *  Created on: 2019-05-01
 *      Author: Joseph Haske
 */

#ifndef MODELHANDLER_H_
#define MODELHANDLER_H_

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

class ModelHandler {

	struct Triangles
	{
		int vert[3];
	};

	struct Materials
	{
		std::string matName;
		float emission[4], ambient[4], diffuse[4], specular[4], shininess;
	};

	struct Vertices
	{
		/**
		 * 0 = x
		 * 1 = y
		 * 2 = z
		 */
		float coord[3];
	};

public:
	ModelHandler();
	virtual ~ModelHandler();

	void draw();
	void loadModel(std::string fileName);

	Vertices v[100];
	Triangles t[100];
	Materials m[10];
	int numVertices;
	int numTriangles;
	int numMaterials;
};

#endif /* MODELHANDLER_H_ */
