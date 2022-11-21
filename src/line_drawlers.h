#ifndef LINE_DRAWLERS_H
#define LINE_DRAWLERS_H

#include "SFML/Graphics/Image.hpp"
#include <SFML/Graphics.hpp>

struct Line {
  sf::Vector2f start;
  sf::Vector2f end;
};

class LineDrawler {
public:
  virtual ~LineDrawler() = default;

  virtual void draw_line(Line line, const sf::Color &color,
                         sf::Image &image) const = 0;
};

class SimpleLineDrawler : public LineDrawler {
public:
  void draw_line(Line line, const sf::Color &color,
                 sf::Image &image) const override;
};

class DdaLineDrawler : public LineDrawler {
public:
  void draw_line(Line line, const sf::Color &color,
                 sf::Image &image) const override;
};


#endif
