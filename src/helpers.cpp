#include "helpers.hpp"

#include <GL/glew.h>
#include <stdio.h>

GLFWwindow* initWindow() {
  GLFWwindow* window;
  // Initialise GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return nullptr;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE);  // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Main", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr,
            "Failed to open GLFW window. If you have an Intel GPU, they are "
            "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true;  // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return nullptr;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  // Hide the mouse and enable unlimited mouvement
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Set the mouse at the center of the screen
  glfwPollEvents();
  glfwSetCursorPos(window, 1024 / 2, 768 / 2);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
  return window;
}

void collide(std::vector<FireBall>& fireBalls, std::vector<Object>& objects) {
  for (auto ballIt = fireBalls.begin(); ballIt != fireBalls.end();) {
    bool deleted = false;
    for (auto objectIt = objects.begin(); objectIt != objects.end();
         ++objectIt) {
      if (glm::distance(ballIt->getPosition(), objectIt->getPosition()) <
          FireBall::colliderRadius + Object::colliderRadius) {
        deleted = true;
        objects.erase(objectIt);
        ballIt = fireBalls.erase(ballIt);
        break;
      }
    }
    if (!deleted) ++ballIt;
  }
}