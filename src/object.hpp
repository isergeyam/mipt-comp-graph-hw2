#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <random>

class Object {
 public:
  Object();
  void draw();
  glm::vec3 getPosition();

 public:
  static bool init();
  static void finalize();

 public:
  static constexpr float colliderRadius = 1.0f;

 private:
  glm::mat4 ModelMatrix;
  glm::vec3 position;

 private:
  static GLuint vertexBuffer;
  static GLuint uvBuffer;
  static GLuint MatrixID;
  static GLuint programID;
  static GLuint TextureID;
  static GLuint Texture;
  static size_t verticesCount;
  static std::random_device rd;
  static std::mt19937 generator;
  static std::uniform_real_distribution<float> uniform_distrib;
  static std::uniform_real_distribution<float> uniform_distrib_angle;
};