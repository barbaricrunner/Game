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
#include "IncludeMethods.h"

int main(void)
{
	ModelHandler mh;
	mh.loadModel("./Models/cube.dae");
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
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glRotatef(0.f, 0.f, (float) glfwGetTime() * 50.f, 1.f);
        mh.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
