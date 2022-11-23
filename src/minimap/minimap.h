#ifndef MINIMAP_H
#define MINIMAP_H

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class MiniMap {
public:
  virtual ~MiniMap() = default;

  virtual void set_pixel(const sf::Vector2i &pos, const sf::Color &color) = 0;

  virtual sf::Color get_pixel(const sf::Vector2i &pos) const = 0;

  virtual sf::IntRect get_size() const = 0;

  virtual void draw(sf::RenderTarget &render) const = 0;
};

#endif
