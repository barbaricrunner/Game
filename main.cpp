/*
 * main.cpp
 *
 *  Created on: 2019-05-01
 *      Author: Joseph Haske
 */

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "Assets/ModelHandler.h"

float worldX, worldY, worldZ;
float worldXVel, worldYVel, worldZVel;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if(key == GLFW_KEY_W && action == GLFW_PRESS)
    	worldYVel += 0.5f;
    else if(key == GLFW_KEY_S && action == GLFW_PRESS)
    	worldYVel -= 0.5f;
    else if(key == GLFW_KEY_A && action == GLFW_PRESS)
    	worldXVel -= 0.5f;
    else if(key == GLFW_KEY_D && action == GLFW_PRESS)
    	worldXVel = 0.5f;
    else if(key == GLFW_KEY_W && action == GLFW_RELEASE)
		worldYVel = 0.0f;
	else if(key == GLFW_KEY_S && action == GLFW_RELEASE)
		worldYVel = 0.0f;
	else if(key == GLFW_KEY_A && action == GLFW_RELEASE)
		worldXVel = 0.0f;
    else if(key == GLFW_KEY_D && action == GLFW_RELEASE)
    	worldXVel = 0.0f;
}

int main(void)
{
	ModelHandler mh;
	mh.loadModel("./Models/colorcube.dae");
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Game", NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }//end if(!window)

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = 50.0f * width / (float) height;
        glViewport(0, 0, width, height);
        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        //clear the depth and color buffers
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -50.f, 50.f, 50.f, -50.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
        worldX += worldXVel;
        worldY += worldYVel;
        worldZ += worldZVel;
        glTranslatef(worldX, worldY, worldZ);
        mh.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
