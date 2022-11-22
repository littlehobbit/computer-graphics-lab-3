#include "filler.h"
#include "SFML/System/Vector2.hpp"

#include <cmath>
#include <stack>

void RecursiveFiller::fill(const sf::Vector2f &start,
                           const sf::Color &fill_color,
                           const sf::Color &border_color,
                           MiniMap &minimap) const {
  std::stack<sf::Vector2i> points;
  points.push({(int)std::round(start.x), (int)std::round(start.y)});

  while (!points.empty()) {
    auto point = points.top();
    points.pop();

    if (point.x < 0 || point.x > minimap.get_size().width || point.y < 0 ||
        point.y > minimap.get_size().height) {
      continue;
    }

    if (minimap.get_pixel(point) == border_color ||
        minimap.get_pixel(point) == fill_color) {
      continue;
    }

    minimap.set_pixel(point, fill_color);

    points.push(point + sf::Vector2i{-1, 0});
    points.push(point + sf::Vector2i{1, 0});
    points.push(point + sf::Vector2i{0, 1});
    points.push(point + sf::Vector2i{0, -1});

    // TODO: show image after draw pixel
  }
}

void ScanningLineFiller::fill(const sf::Vector2f &start,
                              const sf::Color &fill_color,
                              const sf::Color &border_color,
                              MiniMap &minimap) const {
  std::stack<sf::Vector2i> points;
  points.push({(int)std::round(start.x), (int)std::round(start.y)});

  while (!points.empty()) {
    auto point = points.top();
    points.pop();

    if (minimap.get_pixel(point) == fill_color ||
        minimap.get_pixel(point) == border_color) {
      continue;
    }

    auto left = point.x, right = point.x;
    while (left > 0 && minimap.get_pixel({left - 1, point.y}) != border_color) {
      left--;
    }
    while (right < minimap.get_size().width &&
           minimap.get_pixel({right, point.y}) != border_color) {
      right++;
    }

    for (int i = left; i < right; i++) {
      minimap.set_pixel({i, point.y}, fill_color);
    }

    // TODO: counters
    //   countFill += right - left;
    //   countLine -= right - left;

    bool top_new = true;
    bool botom_new = true;
    for (int i = right - 1; i > left; i--) {
      // TODO: occure multiple stack insertion
      if (point.y + 1 < minimap.get_size().height &&
          minimap.get_pixel({i, point.y + 1}) != border_color &&
          minimap.get_pixel({i, point.y + 1}) != fill_color) {
        if (top_new) {
          points.emplace(i, point.y + 1);
          top_new = false;
        }
      } else {
        top_new = true;
      }

      if (point.y > 1 && minimap.get_pixel({i, point.y - 1}) != border_color &&
          minimap.get_pixel({i, point.y - 1}) != fill_color) {
        if (botom_new) {
          points.emplace(i, point.y - 1);
          botom_new = false;
        }
      } else {
        botom_new = true;
      }
    }
  }
}
