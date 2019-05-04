/*
 * main.cpp
 *
 *  Created on: 2019-05-01
 *      Author: Joseph Haske
 */

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "Interface/WindowHandler.h"

int main(void)
{
    WindowHandler wh;
    wh.createWindow();

    exit(EXIT_SUCCESS);
}
