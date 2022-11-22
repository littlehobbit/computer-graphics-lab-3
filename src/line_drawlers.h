#ifndef LINE_DRAWLERS_H
#define LINE_DRAWLERS_H

#include "minimap.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

struct Line {
  sf::Vector2f start;
  sf::Vector2f end;
};

class LineDrawler {
public:
  virtual ~LineDrawler() = default;

  virtual void draw_line(Line line, const sf::Color &color,
                         MiniMap &image) const = 0;
};

class SimpleLineDrawler : public LineDrawler {
public:
  void draw_line(Line line, const sf::Color &color,
                 MiniMap &image) const override;
};

class DdaLineDrawler : public LineDrawler {
public:
  void draw_line(Line line, const sf::Color &color,
                 MiniMap &image) const override;
};

#endif
