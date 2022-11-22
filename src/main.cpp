#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>

#include "CLI/App.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include "filler.h"
#include "line_drawlers.h"
#include "minimap.h"
#include "triangle.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <CLI/CLI.hpp>

#include <cmath>

// TODO: collect drawed pixel count & time of drawing
template <typename Drawler> class MetricDrawlerDecorator : public Drawler {
public:
  using Base = Drawler;
  void draw_line(Line line, const sf::Color &color,
                 MiniMap &image) const override {
    // TODO: start timer
    Base::draw_line(line, color, image);
    // TODO: end timer
    // TODO: print result
  }
};

template <typename Filler> class MetricFillerDecorator : public Filler {
public:
  using Base = Filler;
  void fill(const sf::Vector2f &start, const sf::Color &fill_color,
            const sf::Color &border_color, MiniMap &image) const override {
    // TODO: start timer
    Base::fill(start, fill_color, border_color, image);
    // TODO: end timer
    // TODO: print result
  }
};

void show_coords(sf::RenderWindow &window, uint32_t pixel_width);

// TODO: счетчики (посмотреть какие нада)
int main(int argc, char *argv[]) {
  CLI::App app("triangle drawler", "lab-3");

  double triangular_side = 100;
  double angle = 30;

  uint16_t pixel_width = 4;

  std::string fill_algorithm = "recursive";
  std::string line_algorithm = "dda";

  bool is_show_coords = false;

  app.add_flag("-c", is_show_coords);

  app.add_option("-l,--length", triangular_side, "Length of triangular side")
      ->default_val(triangular_side);
  app.add_option("-a,--angle", angle, "Angle between sides")
      ->default_val(angle);

  app.add_option("-p,--pixel-width", pixel_width, "Size of pixel");

  app.add_option("--line", line_algorithm, "Line algorithm")
      ->default_val(line_algorithm);
  app.add_option("--fill", fill_algorithm, "Fill algorithm")
      ->default_val(fill_algorithm);

  CLI11_PARSE(app, argc, argv);

  std::shared_ptr<LineDrawler> line_drawler;

  if (line_algorithm == "dda") {
    line_drawler = std::make_shared<DdaLineDrawler>();
  } else if (line_algorithm == "simple") {
    line_drawler = std::make_shared<SimpleLineDrawler>();
  } else {
    std::cerr << "Incorrect line algo\n";
    return 1;
  }

  std::shared_ptr<Filler> filler;
  if (fill_algorithm == "recursive") {
    filler = std::make_shared<RecursiveFiller>();
  } else if (fill_algorithm == "scan") {
    filler = std::make_shared<ScanningLineFiller>();
  } else {
    std::cerr << "Incorrect fill algo\n";
    return 1;
  }

  const auto half_angle = angle / 2 * M_PI / 180.0;
  const auto height = triangular_side * std::cos(half_angle);
  const auto width = 2 * triangular_side * std::sin(half_angle);

  const auto offset = 5;
  const size_t screen_width = width + 2 * offset;
  const size_t screen_height = height + 2 * offset;

  const auto top_point = sf::Vector2f{std::round(screen_width / 2.0f), offset * 1.0f};
  const auto left_point =
      sf::Vector2f(std::round(top_point.x - width / 2), std::round(top_point.y + height));
  const auto right_point =
      sf::Vector2f(std::round(top_point.x + width / 2), std::round(top_point.y + height));

  Triangle triangle({left_point, top_point, right_point});

  triangle.set_line_drawler(line_drawler);

  auto small_triangles = triangle.split_by_medians();
  for (auto &tr : small_triangles) {
    tr.set_line_drawler(line_drawler);
    tr.set_filler(filler);

    tr.set_border_color(
        sf::Color{(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()});
    tr.set_fill_color(
        sf::Color{(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()});
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

  PixelPerfectImage image(screen_width, screen_height, pixel_width);
  triangle.draw(image);

  for (auto &tr : small_triangles) {
    tr.draw(image);
  }

  for (auto &median : medians_centers) {
    line_drawler->draw_line(median, sf::Color::Magenta, image);
  }

  sf::RenderWindow window(
      sf::VideoMode(image.get_size().width, image.get_size().height), "lab-3");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);
    image.draw(window);

    if (is_show_coords) {
      show_coords(window, pixel_width);
    }

    window.display();
  }
}

void show_coords(sf::RenderWindow &window, uint32_t pixel_width) {
  for (float y = 1; y < window.getSize().y; y += pixel_width) {
    sf::Vertex horizontal_line[] = {
        {sf::Vector2f{0, y}, sf::Color::Red},
        {sf::Vector2f(window.getSize().x, y), sf::Color::Red}};

    window.draw(horizontal_line, 2, sf::PrimitiveType::Lines);
  }

  for (float x = 1; x < window.getSize().x; x += pixel_width) {

    sf::Vertex vertial_line[] = {
        {sf::Vector2f{x, 0}, sf::Color::Red},
        {sf::Vector2f(x, window.getSize().y), sf::Color::Red}};

    window.draw(vertial_line, 2, sf::PrimitiveType::Lines);
  }
}