#ifndef SIMPLE_LINE_DRAWLER_H
#define SIMPLE_LINE_DRAWLER_H

#include "line_drawler.h"
#include <cmath>
#include <limits>

#include "utils.h"

class SimpleLineDrawler : public LineDrawler {
public:
  size_t draw_line(Line line, const sf::Color &color,
                   MiniMap &image) const override {
    size_t pixels_drawed = 0;
    auto start = to_vec2i(line.start), end = to_vec2i(line.end);
    if (start.x > end.x || (start.x == end.x && start.y > end.y)) {
      auto t = start;
      start = end;
      end = t;
    }

    double k = (end.y - start.y) / double(end.x - start.x);
    double x = start.x;
    double y = start.y;

    if (start.x == end.x) {
      while (y < std::round(end.y)) {
        image.set_pixel({static_cast<int>(x), static_cast<int>(y)}, color);
        pixels_drawed++;
        y += 1.0;
      }
    } else {
      while (x < std::round(end.x)) {
        int bottom_y = std::round(std::min(std::round(y), std::round(y + k)));
        int top_y = std::round(std::max(std::round(y), std::round(y + k)));
        for (int i = bottom_y; i <= top_y; i++) {
          image.set_pixel({(int)std::round(x), i}, color);
          pixels_drawed++;
        }
        y += k;
        x += 1.0;
      }
    }

    return pixels_drawed;
  }
};

#endif
