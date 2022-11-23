#ifndef UTILS_H
#define UTILS_H

#include "SFML/System/Vector2.hpp"

#include <cmath>

inline sf::Vector2i to_vec2i(const sf::Vector2f &point) {
  return {(int)(std::round(point.x)), (int)(std::round(point.y))};
}

#endif
