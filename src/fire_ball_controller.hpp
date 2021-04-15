#pragma once
#include <vector>

#include "fire_ball.hpp"

class FireBallController {
 public:
  void process_events();
  std::vector<FireBall>& getFireBalls();
  

 private:
  std::vector<FireBall> fireBalls;
};