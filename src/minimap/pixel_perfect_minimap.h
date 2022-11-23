#ifndef PIXEL_PERFECT_MINIMAP_H
#define PIXEL_PERFECT_MINIMAP_H

#include "minimap.h"

class PixelPerfectImage : public MiniMap {
public:
  PixelPerfectImage(int width, int height, int pixel_width);

  void set_pixel(const sf::Vector2i &pos, const sf::Color &color) override;

  sf::Color get_pixel(const sf::Vector2i &pos) const override;

  sf::IntRect get_size() const override;

  void draw(sf::RenderTarget &render) const override;

private:
  sf::Image _image;
  int _pixel_width;
};

#endif
