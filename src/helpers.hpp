#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "fire_ball.hpp"
#include "object.hpp"

GLFWwindow* initWindow();

size_t collide(std::vector<FireBall> &fireBalls, std::vector<Object> &objects);