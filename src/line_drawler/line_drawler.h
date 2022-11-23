#ifndef LINE_DRAWLER_H
#define LINE_DRAWLER_H

#include "minimap/minimap.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

struct Line {
  sf::Vector2f start;
  sf::Vector2f end;
};

class LineDrawler {
public:
  virtual ~LineDrawler() = default;

  virtual size_t draw_line(Line line, const sf::Color &color,
                         MiniMap &image) const = 0;
};



#endif
