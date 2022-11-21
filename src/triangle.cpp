#include "triangle.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/System/Vector2.hpp"

#include <cstdio>
#include <numeric>

sf::Vector2f Triangle::get_median_intersection() const {
  const auto sum = _points[0] + _points[1] + _points[2];
  return {sum.x / 3, sum.y / 3};
}

sf::Vector2f Triangle::middle_line(const sf::Vector2f &lhs,
                                   const sf::Vector2f &rhs) {
  return {(lhs.x + rhs.x) / 2, (lhs.y + rhs.y) / 2};
}

std::vector<Line> Triangle::get_medians() const {
  return {
      {_points[0], middle_line(_points[1], _points[2])},
      {_points[1], middle_line(_points[0], _points[2])},
      {_points[2], middle_line(_points[0], _points[1])},
  };
}

// TODO: move border_color & fill_color to class members
void Triangle::draw(sf::Image &image, const sf::Color &border_color,
                    const sf::Color &fill_color) const {
  if (_drawler) {
    _drawler->draw_line({_points[0], _points[1]}, border_color, image);
    _drawler->draw_line({_points[1], _points[2]}, border_color, image);
    _drawler->draw_line({_points[2], _points[0]}, border_color, image);
  }

  if (_filler) {
    _filler->fill(get_median_intersection(), fill_color, border_color, image);
  }
}

std::vector<Triangle> Triangle::split_by_medians() const {
  auto center = get_median_intersection();

  std::vector<Triangle> triangles;

  std::vector<sf::Vector2f> middle_points = {
      middle_line(_points[0], _points[1]), middle_line(_points[1], _points[2]),
      middle_line(_points[2], _points[0])};

  auto current = middle_points.back();
  for (int i = 0; i < _points.size(); i++) {
    triangles.push_back(std::vector<sf::Vector2f>{center, _points[i], current});
    current = middle_points[i];
    triangles.push_back(std::vector<sf::Vector2f>{center, _points[i], current});
  }

  return triangles;
}
