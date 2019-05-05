/*
 * ModelLoader.h
 *
 *  Created on: May 5, 2019
 *      Author: user1
 */

#ifndef MODELLOADER_H_
#define MODELLOADER_H_

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

#include "../Math/Vec3D.h"
#include "../Math/Vec4D.h"

#include "Model.h"

class ModelLoader {

public:
	ModelLoader(std::string &fileN, Model &m);
	virtual ~ModelLoader();

	void loadModel();
private:
	Model model;
	std::string fileName;
	Vec3D<GLfloat> scale; /**< A scaling vector */

	int removeTags(std::string &line, std::regex &numRegex, std::string *returnArray);
	void processMaterial(std::string &line);
	void processVertex(std::string &line);
	void processTriangle(std::string &line);
	void scaleModel();
	void removeExponents(std::string &line);
	void getFloat4D(std::string &line, Vec4D<GLfloat> &v);
};

#endif /* MODELLOADER_H_ */
