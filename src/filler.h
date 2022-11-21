#ifndef FILLER_H
#define FILLER_H

#include <SFML/Graphics.hpp>

class Filler {
public:
  virtual ~Filler() = default;

  virtual void fill(const sf::Vector2f &start, const sf::Color &fill_color,
                    const sf::Color &border_color, sf::Image &image) const = 0;
};

class RecursiveFiller : public Filler {
public:
  void fill(const sf::Vector2f &start, const sf::Color &fill_color,
            const sf::Color &border_color, sf::Image &image) const override;
};

class ScanningLineFiller : public Filler {
public:
  void fill(const sf::Vector2f &start, const sf::Color &fill_color,
            const sf::Color &border_color, sf::Image &image) const override;
};

#endif
