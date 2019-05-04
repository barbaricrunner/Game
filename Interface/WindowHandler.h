/*
 * WindowHandler.h
 *
 *  Created on: May 3, 2019
 *      Author: user1
 */

#ifndef WINDOWHANDLER_H_
#define WINDOWHANDLER_H_

#include <GLFW/glfw3.h>

class WindowHandler {
public:
	WindowHandler();
	virtual ~WindowHandler();

	GLFWwindow createWindow();
};

#endif /* WINDOWHANDLER_H_ */
