#include "object.hpp"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <thread>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
using namespace std::chrono_literals;

#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/shader.hpp>
#include <common/texture.hpp>

Object::Object() {
  position = getPosition() + getDirection() * 20.0f +
             glm::vec3{uniform_distrib(generator), uniform_distrib(generator),
                       uniform_distrib(generator)};

  glm::vec3 rotationAxis{uniform_distrib(generator), uniform_distrib(generator),
                         uniform_distrib(generator)};
  auto rotation_angle = uniform_distrib_angle(generator);

  ModelMatrix = glm::translate(glm::mat4(), position) *
                glm::rotate(glm::mat4(1.0f), rotation_angle, rotationAxis);
}

glm::vec3 Object::getObjectPosition() { return position; }

bool Object::init() {
  generator = std::mt19937(rd());
  uniform_distrib = std::uniform_real_distribution<float>{0.f, 30.f};
  uniform_distrib_angle = std::uniform_real_distribution<float>{0.f, 360.f};
  // Create and compile our GLSL program from the shaders
  programID = LoadShaders("../shaders/TransformVertexShader.glsl",
                          "../shaders/TextureFragmentShader.glsl");

  // Get a handle for our "MVP" uniform
  MatrixID = glGetUniformLocation(programID, "MVP");

  // Load the texture
  Texture = loadDDS("../textures/bricks.dds");

  // Get a handle for our "myTextureSampler" uniform
  TextureID = glGetUniformLocation(programID, "myTextureSampler");

  // Read our .obj file
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;  // Won't be used at the moment.
  if (!loadOBJ("../models/bricks.obj", vertices, uvs, normals)) return false;
  verticesCount = vertices.size();

  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
               &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &uvBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0],
               GL_STATIC_DRAW);
  return true;
}

void Object::draw() {
  // Use our shader
  glUseProgram(programID);

  glm::mat4 ProjectionMatrix = getProjectionMatrix();
  glm::mat4 ViewMatrix = getViewMatrix();
  // ModelMatrix = glm::mat4(1.0f);
  glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // Bind our texture in Texture Unit 0
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Texture);
  // Set our "myTextureSampler" sampler to use Texture Unit 0
  glUniform1i(TextureID, 0);

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(0,         // attribute
                        3,         // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void*)0   // array buffer offset
  );

  // 2nd attribute buffer : UVs
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glVertexAttribPointer(1,         // attribute
                        2,         // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void*)0   // array buffer offset
  );

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, verticesCount);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Object::finalize() {
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &uvBuffer);
  glDeleteProgram(programID);
  glDeleteTextures(1, &Texture);
}

GLuint Object::vertexBuffer;
GLuint Object::uvBuffer;
GLuint Object::MatrixID;
GLuint Object::programID;
GLuint Object::TextureID;
GLuint Object::Texture;
size_t Object::verticesCount;
std::random_device Object::rd;
std::mt19937 Object::generator;
std::uniform_real_distribution<float> Object::uniform_distrib;
std::uniform_real_distribution<float> Object::uniform_distrib_angle;

constexpr float Object::colliderRadius;