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

	struct Material
	{
		std::string matName;
		GLfloat emission[4], ambient[4], diffuse[4], specular[4], shininess;
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

	struct Triangle
	{
		int vert[3];
		Material* m;
	};

public:
	ModelHandler();
	virtual ~ModelHandler();

	void draw();
	void loadModel(std::string fileName);
	int removeTags(std::string &line, std::regex &numRegex, std::string *returnArray);

	Vertices v[100];
	Triangle t[100];
	Material m[10];
	int numVertices;
	int numTriangles;
	int numMaterials;
};

#endif /* MODELHANDLER_H_ */
