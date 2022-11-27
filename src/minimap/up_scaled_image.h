#ifndef UP_SCALED_IMAGE_H
#define UP_SCALED_IMAGE_H

#include "minimap.h"

class UpScaledImage : public MiniMap {
public:
  UpScaledImage(int width, int height, int pixel_width);

  void set_pixel(const sf::Vector2i &pos, const sf::Color &color) override;

  sf::Color get_pixel(const sf::Vector2i &pos) const override;

  sf::IntRect get_size() const override;

  void draw(sf::RenderWindow &render) const override;

protected:
  sf::Image _image;
  int _pixel_width;
};

#endif
