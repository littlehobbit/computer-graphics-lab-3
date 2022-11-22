#include "line_drawlers.h"
#include "SFML/System/Vector2.hpp"
#include "minimap.h"
#include <cmath>

#include <limits>
#include <type_traits>
#include <utility>

void SimpleLineDrawler::draw_line(Line line, const sf::Color &color,
                                  MiniMap &image) const {
  auto start = line.start, end = line.end;
  // std::printf("From (%f,%f) to (%f,%f)\n", start.x, start.y, end.x, end.y);
  // TODO: extract condition
  if (start.x > end.x || (start.x == end.x && start.y > end.y)) {
    auto t = start;
    start = end;
    end = t;
  }

  double k = (end.y - start.y) / (end.x - start.x);
  double x = start.x;
  double y = start.y;

  const auto inf = std::numeric_limits<double>::infinity();
  if (k == inf || k == -inf) {
    while (y < std::round(end.y)) {
      image.set_pixel({static_cast<int>(x), static_cast<int>(y)}, color);
      y++;
    }
  } else {
    while (x < std::round(end.x)) {
      int startI = std::round(std::min(std::round(y), std::round(y + k)));
      int endI = std::round(std::max(std::round(y), std::round(y + k)));
      for (int i = startI; i <= endI; i++) {
        image.set_pixel({(int)std::round(x), i}, color);
      }
      y += k;
      x += 1.0;
    }
  }
}

void DdaLineDrawler::draw_line(Line line, const sf::Color &color,
                               MiniMap &image) const {
  auto &start = line.start, &end = line.end;
  sf::Vector2i start_rounded(std::round(start.x), std::round(start.y));
  sf::Vector2i end_rounded(std::round(end.x), std::round(end.y));

  // TODO: test withound rounded
  int l = std::max(std::abs(end_rounded.x - start_rounded.x),
                   std::abs(end_rounded.y - start_rounded.y));
  float dx = (end.x - start.x) / l;
  float dy = (end.y - start.y) / l;
  auto x = start.x, y = start.y;

  for (int i = 0; i < l; i++) {
    image.set_pixel(
        {static_cast<int>(std::round(x)), static_cast<int>(std::round(y))},
        color);

    x += dx;
    y += dy;
  }
}
