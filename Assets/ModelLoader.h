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
	ModelLoader();
	virtual ~ModelLoader();

	void loadModel(std::string &fileN, Model &model);
private:
	Vec3D<GLfloat> scale; /**< A scaling vector */

	int removeTags(std::string &line, std::regex &numRegex, std::string *returnArray);
	void processMaterial(std::string &line, Model &model);
	void processVertex(std::string &line, Model &model);
	void processTriangle(std::string &line, Model &model);
	void scaleModel();
	void removeExponents(std::string &line);
	void getFloat4D(std::string &line, Vec4D<GLfloat> &v);
};

#endif /* MODELLOADER_H_ */
