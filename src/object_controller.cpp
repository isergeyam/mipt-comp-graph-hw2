#include "object_controller.hpp"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/shader.hpp>
#include <common/texture.hpp>

extern GLFWwindow* window;

void ObjectController::process_events() {
  // Create sphere if mouse was released
  static double lastCreated = glfwGetTime();
  if (lastCreated + 3. < glfwGetTime()) {
    objects.emplace_back();
    lastCreated = glfwGetTime();
  }
  for (auto& object : objects) {
    object.draw();
  }
}

std::vector<Object>& ObjectController::getObjects() { return objects; }