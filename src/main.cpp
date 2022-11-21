#include <cstdio>
#include <iostream>
#include <memory>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "filler.h"
#include "line_drawlers.h"
#include "triangle.h"

// TODO: collect drawed pixel count & time of drawing
template <typename Drawler> class MetricDrawlerDecorator : public Drawler {
public:
  using Base = Drawler;
  void draw_line(Line line, const sf::Color &color,
                 sf::Image &image) const override {
    // TODO: start timer
    Base::draw_line(line, color, image);
    // TODO: end timer
    // TODO: print result
  }
};

template <typename Filler> class MetricFillerrDecorator : public Filler {
public:
  using Base = Filler;
  void fill(const sf::Vector2f &start, const sf::Color &fill_color,
            const sf::Color &border_color, sf::Image &image) const override {
    // TODO: start timer
    Base::fill(start, fill_color, border_color, image);
    // TODO: end timer
    // TODO: print result
  }
};

int main(int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode(800, 800), "lab-3");

  Triangle triangle({{100, 100}, {100, 500}, {500, 100}});

  auto line_drawler =
      std::make_shared<MetricDrawlerDecorator<DdaLineDrawler>>();
  auto filler = std::make_shared<ScanningLineFiller>();
  triangle.set_line_drawler(line_drawler);
  triangle.set_filler(filler);

  auto small_triangles = triangle.split_by_medians();
  for (auto &tr : small_triangles) {
    // tr.set_line_drawler(line_drawler);
  }

  std::vector<Line> medians_centers = {
      {small_triangles.back().get_median_intersection(),
       small_triangles.front().get_median_intersection()}};
  // TODO: переделать
  for (int i = 0; i < small_triangles.size() - 1; i++) {
    medians_centers.push_back(
        {small_triangles[i].get_median_intersection(),
         small_triangles[i + 1].get_median_intersection()});
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);

    sf::Image image;
    image.create(window.getSize().x, window.getSize().y);
    triangle.draw(image, sf::Color::Blue, sf::Color::Green);

    for (auto &tr : small_triangles) {
      tr.draw(image, sf::Color::Yellow, sf::Color::Cyan);
    }

    for (auto &line : medians_centers) {
      line_drawler->draw_line(line, sf::Color::Magenta, image);
    }

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);
    window.draw(sprite);

    // window.draw(sprite);
    window.display();
  }
}