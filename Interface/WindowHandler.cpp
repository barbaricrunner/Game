/*
 * WindowHandler.cpp
 *
 *  Created on: May 3, 2019
 *      Author: Joseph Haske
 */

#include "WindowHandler.h"

WindowHandler::WindowHandler() {
	// TODO Auto-generated constructor stub

}

WindowHandler::~WindowHandler() {
	// TODO Auto-generated destructor stub
}

void WindowHandler::createWindow()
{
	ModelHandler mh;
	mh.loadModel("./Models/colorcube.dae");
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "Game", NULL, NULL);

	if(!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}//end if(!window)

	glfwMakeContextCurrent(window);

	//Setup keyboard
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetKeyCallback(window, key_callback);

	//Setup mouse
	glfwSetScrollCallback(window, scroll_callback);

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = zoomMultiplier * width / (float) height;
		glViewport(0, 0, width, height);
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		//clear the depth and color buffers
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -zoomMultiplier, zoomMultiplier, 30.f, -10.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
		worldX += worldXVel;
		worldY += worldYVel;
		glTranslatef(worldX, worldY, worldZ);
		mh.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	destroyWindow();
}

void WindowHandler::destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
