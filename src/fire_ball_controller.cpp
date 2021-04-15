#include "fire_ball_controller.hpp"

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

void FireBallController::process_events() {
  // Create sphere if mouse was released
  static int oldState = GLFW_RELEASE;
  int newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
    fireBalls.emplace_back();
  }
  oldState = newState;

  for (auto& fireBall : fireBalls) {
    fireBall.draw();
  }
}

std::vector<FireBall>& FireBallController::getFireBalls() { return fireBalls; }