#ifndef RECURSIVE_FILLER_H
#define RECURSIVE_FILLER_H

#include "filler.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <stack>

class RecursiveFiller : public Filler {
public:
  size_t fill(const sf::Vector2f &start, const sf::Color &fill_color,
            const sf::Color &border_color, MiniMap &minimap) const override {
    size_t filled_count = 0;
    std::stack<sf::Vector2i> points;
    points.push({(int)std::round(start.x), (int)std::round(start.y)});

    while (!points.empty()) {
      auto point = points.top();
      points.pop();

      if (is_point_out_of_range(point, minimap.get_size())) {
        continue;
      }

      if (minimap.get_pixel(point) == border_color ||
          minimap.get_pixel(point) == fill_color) {
        continue;
      }

      minimap.set_pixel(point, fill_color);
      filled_count++;

      points.push(point + sf::Vector2i{-1, 0});
      points.push(point + sf::Vector2i{1, 0});
      points.push(point + sf::Vector2i{0, 1});
      points.push(point + sf::Vector2i{0, -1});
    }

    return filled_count;
  }

private:
  bool is_point_out_of_range(const sf::Vector2i &point,
                             const sf::IntRect &minimap_size) const {
    return point.x < 0 || point.x > minimap_size.width || point.y < 0 ||
           point.y > minimap_size.height;
  }
};

#endif
