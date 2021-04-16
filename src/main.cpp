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
#include <common/text2D.hpp>
#include <common/texture.hpp>

#include "fire_ball_controller.hpp"
#include "helpers.hpp"
#include "object.hpp"
#include "object_controller.hpp"

GLFWwindow* window;

int main(void) {
  window = initWindow();
  if (window == nullptr) return -1;
  FireBall::init();
  Object::init();
  size_t collideCount = 0;
  std::string text;

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  FireBallController fireBallController;
  ObjectController objectController(10);

  // Initialize our little text library with the Holstein font
  initText2D("../textures/Holstein.DDS");

  do {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    computeMatricesFromInputs();

    fireBallController.process_events();
    objectController.process_events();
    collideCount += collide(fireBallController.getFireBalls(),
                            objectController.getObjects());

    // For the next frame, the "last time" will be "now"
    setLastTime(getCurrentTime());

    text = "Score: " + std::to_string(collideCount);
    printText2D(text.data(), 10, 500, 60);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  // Cleanup VBO and shader
  FireBall::finalize();
  Object::finalize();
  glDeleteVertexArrays(1, &VertexArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
