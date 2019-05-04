/*
 * WindowHandler.h
 *
 *  Created on: May 3, 2019
 *      Author: Joseph Haske
 */

#ifndef WINDOWHANDLER_H_
#define WINDOWHANDLER_H_

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Assets/ModelHandler.h"

class WindowHandler{
public:
	WindowHandler();
	virtual ~WindowHandler();

	void createWindow();
	void updateWindow();
	void destroyWindow();

private:
	GLFWwindow* window;
	float worldX, worldY, worldZ;

};

static float zoomMultiplier = 50.0f;
static float worldXVel, worldYVel;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float zoomVelocity = 0.0f;

	if (zoomMultiplier <= 10.0f) zoomVelocity = 0.5f;
	else zoomVelocity = 1.0f;
	if(yoffset > 0.0f) zoomMultiplier -= zoomVelocity;
	else zoomMultiplier += zoomVelocity;

	if(zoomMultiplier > 50.0f) zoomMultiplier = 50.0f;
	else if (zoomMultiplier < 2.0f) zoomMultiplier = 2.0f;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if(key == GLFW_KEY_W && action == GLFW_PRESS)
    	worldYVel -= 0.5f;
    else if(key == GLFW_KEY_S && action == GLFW_PRESS)
    	worldYVel += 0.5f;
    else if(key == GLFW_KEY_A && action == GLFW_PRESS)
    	worldXVel += 0.5f;
    else if(key == GLFW_KEY_D && action == GLFW_PRESS)
    	worldXVel -= 0.5f;
    else if(key == GLFW_KEY_W && action == GLFW_RELEASE)
		worldYVel = 0.0f;
	else if(key == GLFW_KEY_S && action == GLFW_RELEASE)
		worldYVel = 0.0f;
	else if(key == GLFW_KEY_A && action == GLFW_RELEASE)
		worldXVel = 0.0f;
    else if(key == GLFW_KEY_D && action == GLFW_RELEASE)
    	worldXVel = 0.0f;
}

#endif /* WINDOWHANDLER_H_ */
