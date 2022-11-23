#ifndef SCANNING_LINE_FILLER_H
#define SCANNING_LINE_FILLER_H

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "filler.h"
#include "minimap/minimap.h"

#include <cmath>
#include <stack>

class ScanningLineFiller : public Filler {
public:
  size_t fill(const sf::Vector2f &start, const sf::Color &fill_color,
              const sf::Color &border_color, MiniMap &minimap) const override {
    std::stack<sf::Vector2i> points;
    points.push({(int)std::round(start.x), (int)std::round(start.y)});
    size_t filled = 0;

    while (!points.empty()) {
      auto point = points.top();
      points.pop();

      if (minimap.get_pixel(point) == fill_color ||
          minimap.get_pixel(point) == border_color) {
        continue;
      }

      auto left = most_left_unfilled_point(minimap, border_color, point);
      auto right = most_right_unfilled_point(minimap, border_color, point);
      filled += fill_line(minimap, left, right, fill_color);

      add_top_unfilled(points, left, right, fill_color, border_color, minimap);
      add_bottom_unfilled(points, left, right, fill_color, border_color,
                          minimap);
    }

    return filled;
  }

private:
  size_t fill_line(MiniMap &image, const sf::Vector2i &start,
                   const sf::Vector2i &end, const sf::Color &color) const {
    for (int i = start.x; i < end.x; i++) {
      image.set_pixel({i, start.y}, color);
    }

    return end.x - start.x;
  }

  sf::Vector2i most_left_unfilled_point(const MiniMap &minimap,
                                        sf::Color border_color,
                                        sf::Vector2i start_point) const {
    auto left = start_point.x;
    while (left > 0 &&
           minimap.get_pixel({left - 1, start_point.y}) != border_color) {
      left--;
    }
    return {left, start_point.y};
  }

  sf::Vector2i most_right_unfilled_point(const MiniMap &minimap,
                                         sf::Color border_color,
                                         sf::Vector2i start_point) const {
    auto right = start_point.x;
    while (right < minimap.get_size().width &&
           minimap.get_pixel({right, start_point.y}) != border_color) {
      right++;
    }

    return {right, start_point.y};
  }

  void add_top_unfilled(std::stack<sf::Vector2i> &points, sf::Vector2i left,
                        sf::Vector2i right, sf::Color fill, sf::Color border,
                        const MiniMap &minimap) const {

    bool top_new = true;
    for (auto i = sf::Vector2i{left.x, left.y + 1}; i.x < right.x; i.x++) {
      if (i.y < minimap.get_size().height && minimap.get_pixel(i) != border &&
          minimap.get_pixel(i) != fill) {
        points.push(i);
        top_new = false;
      } else {
        top_new = true;
      }
    }
  }

  void add_bottom_unfilled(std::stack<sf::Vector2i> &points, sf::Vector2i left,
                           sf::Vector2i right, sf::Color fill, sf::Color border,
                           const MiniMap &minimap) const {
    bool botom_new = true;
    for (auto i = sf::Vector2i{left.x, left.y - 1}; i.x < right.x; i.x++) {
      if (i.y > 1 && minimap.get_pixel(i) != border &&
          minimap.get_pixel(i) != fill) {
        if (botom_new) {
          points.push(i);
          botom_new = false;
        }
      } else {
        botom_new = true;
      }
    }
  }
};

#endif
