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
    float color1 = 1.0f;
    float color2 = 0.0f;
    float color3 = 0.0f;
    for(int i = 0; i < numTriangles; i++)
    {
    	for(int j = 0; j < 3; j++)
    	{
    	    glColor3f(color1, color2, color3);
    		glVertex3f(v[t[i].vert[j]].coord[0], v[t[i].vert[j]].coord[1], v[t[i].vert[j]].coord[2]);
    		color2 += 0.01;
    		color3 += 0.01;
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
	std::regex triangleRegex(".+<p>.+");
	std::regex stripRegex(".+<.+>");
	std::regex stripRegex1("</.+>");
	std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");
	std::regex intRegex("[0-9]+");

	numTriangles = 0;
	numVertices = 0;

	if(file.is_open())
	{
		std::cout << fileName << '\n';

		//load each line for processing
		while(std::getline(file, line))
		{
			//Check if the line contains the vertex positions
			if(std::regex_match(line, positionRegex))
			{
				//strip the end </...> first to allow for searching for <...>
				//Leaves only the numbers, space delimited
				line = std::regex_replace(std::regex_replace(line, stripRegex1, ""), stripRegex, "");

				//separate each digit out into numbers
				std::smatch matches;
				int coordNum = 0;
				while(regex_search(line, matches, floatRegex))
				{
					std::string temp = matches[0];
					v[numVertices].coord[coordNum++] = std::strtof(temp.c_str(), NULL);
					line = std::regex_replace(line, floatRegex, "", std::regex_constants::format_first_only);
					coordNum%=3;
					if(coordNum == 0) numVertices++;
				}
			}
			//Check if the line contains the triangles
			else if(std::regex_match(line, triangleRegex))
			{
				line = std::regex_replace(std::regex_replace(line, stripRegex1, ""), stripRegex, "");

				std::smatch matches;
				int vertNum = 0;
				while(regex_search(line, matches, intRegex))
				{
					std::string temp = matches[0];
					t[numTriangles].vert[vertNum++] = std::stoi(temp.c_str(), NULL);
					line = std::regex_replace(line, intRegex, "", std::regex_constants::format_first_only);
					line = std::regex_replace(line, intRegex, "", std::regex_constants::format_first_only);
					vertNum%=3;
					if(vertNum == 0) numTriangles++;
				}
			}
			//Check if the line contains materials
			//else if
		}
		file.close();
	}
	else if(file.fail())
	{
		std::cout << "Failed to open file: " << fileName << '\n';
	}
}
