#ifndef FILLER_H
#define FILLER_H

#include <SFML/Graphics.hpp>

#include "minimap/minimap.h"

class Filler {
public:
  virtual ~Filler() = default;

  virtual size_t fill(const sf::Vector2f &start, const sf::Color &fill_color,
                    const sf::Color &border_color, MiniMap &minimap) const = 0;
};

#endif
