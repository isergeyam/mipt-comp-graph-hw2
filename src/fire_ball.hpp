#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>

class FireBall {
 public:
  FireBall();
  void draw();
  glm::vec3 getPosition();

 private:
  glm::vec3 position;
  glm::vec3 direction;

 public:
  static bool init();
  static void finalize();

 public:
  static constexpr float colliderRadius = 1.0f;

 private:
  static GLuint vertexBuffer;
  static GLuint uvBuffer;
  static GLuint MatrixID;
  static GLuint programID;
  static GLuint TextureID;
  static GLuint Texture;
  static size_t verticesCount;

  static constexpr float ballSpeed = 0.05f;
};