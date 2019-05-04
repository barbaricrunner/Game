/*
 * ModelHandler.cpp
 *
 *  Created on: 2019-05-01
 *      Author: Joseph Haske
 */

#include "ModelHandler.h"

ModelHandler::ModelHandler() {
	// TODO Auto-generated constructor stub

}

ModelHandler::~ModelHandler() {
	// TODO Auto-generated destructor stub
}


void ModelHandler::draw()
{
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < numTriangles; i++)
    {
	    glColor3f(t[i].m->specular[0], t[i].m->specular[1], t[i].m->specular[2]);
    	for(int j = 0; j < 3; j++)
    	{
    		glVertex3f(v[t[i].vert[j]].coord[0], v[t[i].vert[j]].coord[1], v[t[i].vert[j]].coord[2]);
    	}
    }
    glEnd();
}

/**
 * Loads in the model from a collada file
 */
void ModelHandler::loadModel(std::string fileName)
{
	std::string line;

	std::ifstream file(fileName);

	std::regex positionRegex(".+<float_array.+mesh-positions-array.+>.+<.+>");
	std::regex triangleMatRegex(".+<triangles.+material.+>");
	std::regex triangleRegex(".+<p>.+");
	std::regex materialRegex(".+<effect.+>");
	std::regex emissionRegex(".+<color.+emission.+>.+<.+>");
	std::regex ambientRegex(".+<color.+ambient.+>.+<.+>");
	std::regex diffuseRegex(".+<color.+diffuse.+>.+<.+>");
	std::regex specularRegex(".+<color.+specular.+>.+<.+>");

	std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");
	std::regex intRegex("[0-9]+");
	std::regex matNameRegex("[a-zA-Z0-9]+[-]{1}effect");
	std::regex triangleMatNameRegex("[a-zA-Z0-9]+[-]{1}material");

	numTriangles = 0;
	numVertices = 0;
	numMaterials = 0;

	Material* tempMat;

	if(file.is_open())
	{
		std::cout << fileName << '\n';

		//load each line for processing
		while(std::getline(file, line))
		{
			//Check if the line contains the vertex positions
			if(std::regex_match(line, positionRegex))
			{
				std::string temp[300];
				int numElements = removeTags(line, floatRegex, temp);
				int coordNum = 0;
				for(int i = 0; i < numElements && !temp[i].empty(); i++)
				{
					v[numVertices].coord[coordNum++] = std::strtof(temp[i].c_str(), NULL);
					coordNum%=3;
					if(coordNum == 0) numVertices++;
				}
			}
			//find each triangle material
			else if(std::regex_match(line, triangleMatRegex))
			{
				std::smatch matches;
				std::regex_search(line, matches, triangleMatNameRegex);
				std::string temp = matches[0];
				for(int i = 0; i < numMaterials; i++)
				{
					if(temp == m[i].matName)
					{
						tempMat = &m[i];
					}
				}
			}
			//Check if the line contains the triangles
			else if(std::regex_match(line, triangleRegex))
			{
				std::string temp[300];
				int numElements = removeTags(line, intRegex, temp);
				int vertNum = 0;
				//skip every other number
				for(int i = 0; i < numElements && !temp[i].empty(); i+=2)
				{
					t[numTriangles].vert[vertNum++] = std::stoi(temp[i].c_str(), NULL);
					vertNum%=3;
					if(vertNum == 0)
					{
						t[numTriangles].m = tempMat;
						numTriangles++;
					}
				}
			}
			//Check if the line contains materials
			else if(std::regex_match(line, materialRegex))
			{
				std::smatch matches;
				std::regex_search(line, matches, matNameRegex);

				m[numMaterials].matName = matches[0];

				//rename to material instead of effect
				m[numMaterials].matName = std::regex_replace(m[numMaterials].matName, std::regex("effect"), "material");
				numMaterials++;
			}
			//check if the line contains the emission <color sid="emission">0 0 0 1</color>
			else if(std::regex_match(line, emissionRegex))
			{
				std::string temp[4];
				int numElements = removeTags(line, floatRegex, temp);
				for(int i = 0; i < numElements; i++)
				{
					m[numMaterials-1].emission[i] = std::strtof(temp[i].c_str(), NULL);
				}
			}
			//check if the line contains the ambient <color sid="ambient">0 0 0 1</color>
			else if(std::regex_match(line, ambientRegex))
			{
				std::string temp[4];
				int numElements = removeTags(line, floatRegex, temp);
				for(int i = 0; i < numElements; i++)
				{
					m[numMaterials-1].ambient[i] = std::strtof(temp[i].c_str(), NULL);
				}
			}
			//check if the line contains the diffuse <color sid="diffuse">0.01013024 0.007439202 0.64 1</color>
			else if(std::regex_match(line, diffuseRegex))
			{
				std::string temp[4];
				int numElements = removeTags(line, floatRegex, temp);
				for(int i = 0; i < numElements; i++)
				{
					m[numMaterials-1].diffuse[i] = std::strtof(temp[i].c_str(), NULL);
				}
			}
			//check if the line contains the specular <color sid="specular">0.01504615 0.02148593 0.5 1</color>
			else if(std::regex_match(line, specularRegex))
			{
				std::string temp[4];
				int numElements = removeTags(line, floatRegex, temp);
				for(int i = 0; i < numElements; i++)
				{
					m[numMaterials-1].specular[i] = std::strtof(temp[i].c_str(), NULL);
				}
			}
		}
		file.close();
	}
	else if(file.fail())
	{
		std::cout << "Failed to open file: " << fileName << '\n';
	}
	for(int i = 0; i < numTriangles; i++)
	{
		std::cout << "Triangle " << i << ":\n";
		for(int j = 0; j < 3; j++)
		{
			std::cout << "Side " << j << ": " << t[i].vert[j] << '\n';
			std::cout << "Coords ";
			for(int k = 0; k < 3; k++)
			{
				std::cout << v[t[i].vert[j]].coord[k] << ", ";
			}
			std::cout << "\n\n";
		}
		std::cout << "Specular: ";
		for(int j = 0; j < 4; j++)
		{
			std::cout << t[i].m->specular[j] << " ";
		}
		std::cout << "\n------------------------------\n";
	}
}//end loadModel(std::string) method

/**
 * Searches a line and returns an array of strings
 */
int ModelHandler::removeTags(std::string &line, std::regex &numRegex, std::string *returnArray)
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
