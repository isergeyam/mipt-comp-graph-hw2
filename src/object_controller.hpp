#pragma once
#include <vector>

#include "object.hpp"

class ObjectController {
 public:
  void process_events();
  std::vector<Object> &getObjects();
  ObjectController(size_t initialCount);

 private:
  std::vector<Object> objects;
};