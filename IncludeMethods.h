/*
 * IncludeMethods.h
 *
 *  Created on: May 3, 2019
 *      Author: Joseph Haske
 */

#ifndef INCLUDEMETHODS_H_
#define INCLUDEMETHODS_H_

#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

#endif /* INCLUDEMETHODS_H_ */
