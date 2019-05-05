/*
 * ModelLoader.cpp
 *
 *  Created on: May 5, 2019
 *      Author: user1
 */

#include "ModelLoader.h"

ModelLoader::ModelLoader(std::string &fileN, Model &m) {
	fileName = fileN;
	model = m;
	loadModel();
}

ModelLoader::~ModelLoader() {
	// TODO Auto-generated destructor stub
}

/**
 * Loads the model in from a Blender output Collada file.
 *
 * @param fileName A string representing the file name.
 */
void ModelLoader::loadModel()
{
	//Opening of block regular expressions
	std::regex materialBlockStart(".+<library_effects>");
	std::regex vertexBlockStart(".+<source.+positions.+>");
	std::regex triangleBlockStart(".+<triangles.+>");

	//Closing of block regular expressions
	std::regex blockEnd(".+<[.]/(libarary_effects)|(source)|(triangles)>");

	//Misc regular expressions
	std::regex scaleRegex(".+<scale.+");

	std::string line;

	std::ifstream file(fileName);

	if(file.is_open())
	{
		std::cout << fileName << '\n';
		int state = 0; //default 0, material 1, vertex 2, triangle 3

		//load each line for processing
		while(std::getline(file, line))
		{
			//Process chunk of lines
			switch(state)
			{
			case 1: //material
				removeExponents(line);
				processMaterial(line);
				if(std::regex_match(line, blockEnd)) state = 0;
				break;
			case 2: //vertex
				removeExponents(line);
				processVertex(line);
				if(std::regex_match(line, blockEnd)) state = 0;
				break;
			case 3:// triangle
				processTriangle(line);
				if(std::regex_match(line, blockEnd)) state = 0;
				break;
			default:
				//Determine if line is a material
				if(std::regex_match(line, materialBlockStart)) state = 1;
				//Determine if line is a vertex
				else if(std::regex_match(line, vertexBlockStart)) state = 2;
				//Determine if line is a triangle
				else if(std::regex_match(line, triangleBlockStart)) state = 3;
				//Determine if current block is an end and reset state to 0
				break;
			}
		}
		file.close();
	}
	else if(file.fail())
	{
		std::cout << "Failed to open file: " << fileName << '\n';
	}
	scaleModel();
}//end loadModel(std::string) method

/**
 * Processes the materials block
 *
 * @param line
 */
void ModelLoader::processMaterial(std::string &line)
{
	std::regex materialRegex(".+<effect.+>");
	std::regex matNameRegex("[a-zA-Z0-9]+[-]{1}effect");
	std::regex emissionRegex(".+<color.+emission.+>.+<.+>");
	std::regex ambientRegex(".+<color.+ambient.+>.+<.+>");
	std::regex diffuseRegex(".+<color.+diffuse.+>.+<.+>");
	std::regex specularRegex(".+<color.+specular.+>.+<.+>");

	if(std::regex_match(line, materialRegex))
	{
		std::smatch matches;
		std::regex_search(line, matches, matNameRegex);
		std::string str = matches[0];
		std::regex_replace(str, std::regex("effect"), "material");
		model.addMaterial(str);

		//rename to material instead of effect
	}
	else if(std::regex_match(line, emissionRegex))
	{
		Vec4D<GLfloat> tVec;
		getFloat4D(line, tVec);
		model.matSetEmission(tVec);
	}
	else if(std::regex_match(line, ambientRegex))
	{
		Vec4D<GLfloat> tVec;
		getFloat4D(line, tVec);
		model.matSetAmbient(tVec);
	}
	else if(std::regex_match(line, diffuseRegex))
	{
		Vec4D<GLfloat> tVec;
		getFloat4D(line, tVec);
		model.matSetDiffuse(tVec);
	}
	else if(std::regex_match(line, specularRegex))
	{
		Vec4D<GLfloat> tVec;
		getFloat4D(line, tVec);
		model.matSetSpecular(tVec);
	}
}

void ModelLoader::processVertex(std::string &line)
{
	std::regex vertexRegex(".+<float_array.+mesh-positions-array.+>.+<.+>");
	std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");

	std::string temp[1000];
	int numElements = removeTags(line, floatRegex, temp);
	for(int i=0; i<numElements; i+=3)
	{
		model.addVertex(Vec3D<GLfloat>(std::strtof(temp[i].c_str(), NULL), std::strtof(temp[i+1].c_str(), NULL), std::strtof(temp[i+2].c_str(), NULL)));
	}
}

void ModelLoader::processTriangle(std::string &line)
{
	std::regex triangleMatRegex(".+<triangles.+material.+>");
	std::regex triangleMatNameRegex("[a-zA-Z0-9]+[-]{1}material");
	std::regex triangleRegex(".+<p>.+");
	std::regex intRegex("[0-9]+");

	//find each triangle material
	if(std::regex_match(line, triangleMatRegex))
	{
		std::smatch matches;
		std::regex_search(line, matches, triangleMatNameRegex);
		model.setTriangleMaterial(matches[0]);
	}
	//Check if the line contains the triangles
	else if(std::regex_match(line, triangleRegex))
	{
		std::string temp[10000];
		int numElements = removeTags(line, intRegex, temp);
		//skip every other number
		for(int i = 0; i < numElements && !temp[i].empty(); i+=6)
		{
			model.addTriangle(Vec3D<int>(std::stoi(temp[i].c_str(), NULL), std::stoi(temp[i+2].c_str(), NULL), std::stoi(temp[i+4].c_str(), NULL)));
		}
	}
}

void ModelLoader::getFloat4D(std::string &line, Vec4D<GLfloat> &v)
{
	std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");

	std::string temp[4];
	removeTags(line, floatRegex, temp);
	v = Vec4D<GLfloat>(std::strtof(temp[0].c_str(), NULL), std::strtof(temp[1].c_str(), NULL), std::strtof(temp[2].c_str(), NULL), std::strtof(temp[3].c_str(), NULL));
}

/**
 * Searches a line and returns an array of strings
 */
int ModelLoader::removeTags(std::string &line, std::regex &numRegex, std::string *returnArray)
{
	std::regex stripRegex(".+<.+>");
	std::regex stripRegex1("</.+>");

	//strip the end </...> first to allow for searching for <...>
	//Leaves only the numbers, space delimited
	line = std::regex_replace(std::regex_replace(line, stripRegex1, ""), stripRegex, "");

	std::smatch matches;
	int i = 0;
	while(regex_search(line, matches, numRegex))
	{
		returnArray[i++] = matches[0];
		line = std::regex_replace(line, numRegex, "", std::regex_constants::format_first_only);
	}
	return i;
}//end removeTags(std::string line, std::regex, std::regex)

/**
 * Scales the model from the Collada file.
 */
void ModelLoader::scaleModel()
{
	/*for(int i = 0; i < numVertices; i++)
	{
		v[i].coord.scale(scale);
	}*/
}

/**
 * Removes any exponents from the floating point numbers in the Collada file.
 *
 * @param line
 */
void ModelLoader::removeExponents(std::string &line)
{
	std::regex stripRegex("[+-]*[0-9]+[.]{0,1}[0-9]*[e]{1}[-]{1}[0-9]+");

	line = std::regex_replace(line, stripRegex, "0");
}
