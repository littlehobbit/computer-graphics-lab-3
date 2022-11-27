#ifndef DELAY_DECORATOR_H
#define DELAY_DECORATOR_H

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "up_scaled_image.h"

#include <chrono>
#include <thread>

class DelayImageDecorator : public UpScaledImage {
public:
  DelayImageDecorator(int width, int height, int pixel_size,
                      sf::RenderWindow &render, std::chrono::milliseconds delay)
      : UpScaledImage(width, height, pixel_size), _render{render}, _delay{
                                                                       delay} {}

  void set_pixel(const sf::Vector2i &pos, const sf::Color &color) override {
    UpScaledImage::set_pixel(pos, color);
    update_image();
    std::this_thread::sleep_for(_delay);
  }

private:
  void update_image() { UpScaledImage::draw(_render); }

  sf::RenderWindow &_render;
  std::chrono::milliseconds _delay;
};

#endif
ф