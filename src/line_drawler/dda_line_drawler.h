#ifndef DDA_LINE_DRAWLER_H
#define DDA_LINE_DRAWLER_H

#include "line_drawler.h"
#include "utils.h"

#include <cmath>

class DdaLineDrawler : public LineDrawler {
public:
  size_t draw_line(Line line, const sf::Color &color,
                   MiniMap &image) const override {
    size_t pixels_drawed = 0;
    auto &start = line.start, &end = line.end;

    auto start_rounded = to_vec2i(start);
    auto end_rounded = to_vec2i(end);

    int l = std::max(std::abs(end_rounded.x - start_rounded.x),
                     std::abs(end_rounded.y - start_rounded.y));
    float dx = (end.x - start.x) / l;
    float dy = (end.y - start.y) / l;
    auto x = start.x, y = start.y;

    for (int i = 0; i < l; i++) {
      image.set_pixel(
          {static_cast<int>(std::round(x)), static_cast<int>(std::round(y))},
          color);
      pixels_drawed++;

      x += dx;
      y += dy;
    }

    return pixels_drawed;
  }
};

#endif
