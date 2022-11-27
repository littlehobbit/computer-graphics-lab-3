#include "up_scaled_image.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

UpScaledImage::UpScaledImage(int width, int height, int pixel_width)
    : _image(), _pixel_width(pixel_width) {
  _image.create(width * _pixel_width, height * _pixel_width);
}

void UpScaledImage::set_pixel(const sf::Vector2i &pos,
                                  const sf::Color &color) {
  auto start_x = (pos.x - 1) * _pixel_width + 1;
  auto start_y = (pos.y - 1) * _pixel_width + 1;
  for (int x = start_x; x < start_x + _pixel_width; x++) {
    for (int y = start_y; y < start_y + _pixel_width; y++) {
      _image.setPixel(x, y, color);
    }
  }
}

sf::Color UpScaledImage::get_pixel(const sf::Vector2i &pos) const {
  return _image.getPixel(pos.x * _pixel_width, pos.y * _pixel_width);
}

sf::IntRect UpScaledImage::get_size() const {
  return {{},
          {static_cast<int>(_image.getSize().x),
           static_cast<int>(_image.getSize().y)}};
}

void UpScaledImage::draw(sf::RenderWindow &render) const {
  sf::Texture texture;
  texture.loadFromImage(_image);
  sf::Sprite sprite(texture);
  render.clear();
  render.draw(sprite);
  render.display();
}
