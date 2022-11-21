#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <memory>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "filler.h"
#include "line_drawlers.h"

class Triangle {
public:
  Triangle(std::vector<sf::Vector2f> points) : _points{std::move(points)} {}

  void draw(sf::Image &image, const sf::Color &border_color, const sf::Color &fill_color) const;

  sf::Vector2f get_median_intersection() const;

  std::vector<Triangle> split_by_medians() const;

  std::vector<Line> get_medians() const;

  void set_line_drawler(std::shared_ptr<LineDrawler> drawler) {
    _drawler = std::move(drawler);
  }

  void set_filler(std::shared_ptr<Filler> filler) {
    _filler = std::move(filler);
  }

private:
  static sf::Vector2f middle_line(const sf::Vector2f &lhs,
                                  const sf::Vector2f &rhs);

  std::vector<sf::Vector2f> _points;
  std::shared_ptr<LineDrawler> _drawler{nullptr};
  std::shared_ptr<Filler> _filler{nullptr};
};

#endif
