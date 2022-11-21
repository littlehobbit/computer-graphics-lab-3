#include "filler.h"
#include "SFML/System/Vector2.hpp"

#include <cmath>
#include <stack>

void RecursiveFiller::fill(const sf::Vector2f &start,
                           const sf::Color &fill_color,
                           const sf::Color &border_color,
                           sf::Image &image) const {
  std::stack<sf::Vector2i> points;
  points.push({(int)std::round(start.x), (int)std::round(start.y)});

  while (!points.empty()) {
    auto point = points.top();
    points.pop();

    if (point.x < 0 || point.x > image.getSize().x || point.y < 0 ||
        point.y > image.getSize().y) {
      continue;
    }

    if (image.getPixel(point.x, point.y) == border_color ||
        image.getPixel(point.x, point.y) == fill_color) {
      continue;
    }

    image.setPixel(point.x, point.y, fill_color);

    points.push(point + sf::Vector2i{-1, 0});
    points.push(point + sf::Vector2i{1, 0});
    points.push(point + sf::Vector2i{0, 1});
    points.push(point + sf::Vector2i{0, -1});

    // TODO: show image after draw pixel
  }
}

void ScanningLineFiller::fill(const sf::Vector2f &start,
                              const sf::Color &fill_color,
                              const sf::Color &border_color,
                              sf::Image &image) const {
  std::stack<sf::Vector2i> points;
  points.push({(int)std::round(start.x), (int)std::round(start.y)});

  while (!points.empty()) {
    auto point = points.top();
    points.pop();

    if (image.getPixel(point.x, point.y) == fill_color ||
        image.getPixel(point.x, point.y) == border_color) {
      continue;
    }

    auto left = point.x, right = point.x;
    while (left > 0 && image.getPixel(left - 1, point.y) != border_color) {
      left--;
    }
    while (right < image.getSize().x &&
           image.getPixel(right, point.y) != border_color) {
      right++;
    }

    for (int i = left; i < right; i++) {
      image.setPixel(i, point.y, fill_color);
    }

    // TODO: counters
    //   countFill += right - left;
    //   countLine -= right - left;

    bool top_new = true;
    bool botom_new = true;
    for (int i = right - 1; i > left; i--) {
      // TODO: occure multiple stack insertion
      if (point.y + 1 < image.getSize().y &&
          image.getPixel(i, point.y + 1) != border_color &&
          image.getPixel(i, point.y + 1) != fill_color) {
        if (top_new) {
          points.emplace(i, point.y + 1);
          top_new = false;
        }
      } else {
        top_new = true;
      }

      if (point.y > 1 && image.getPixel(i, point.y - 1) != border_color &&
          image.getPixel(i, point.y - 1) != fill_color) {
        if (botom_new) {
          points.emplace(i, point.y - 1);
          botom_new = false;
        }
      } else {
        botom_new = true;
      }
    }
  }
  //   for (int i = left; i < right; i++) {
  //     if (colors.GetLength(1) - 1 > point.Y &&
  //         colors[i, point.Y + 1] != borderColor &&
  //         colors[i, point.Y + 1] != fillColor)
  //       points.Push(new Vector2i(i, point.Y + 1));
  //     if (point.Y >= 1 && colors[i, point.Y - 1] != borderColor &&
  //         colors[i, point.Y - 1] != fillColor)
  //       points.Push(new Vector2i(i, point.Y - 1));
  //   }
  //   if (await) {
  //     Image image = new Image(colors);
  //     Texture texture = new Texture(image);
  //     Sprite sprite = new Sprite(texture);
  //     renderWindow.Clear(SFML.Graphics.Color.Black);
  //     renderWindow.Draw(sprite);
  //     renderWindow.Display();
  //   }
  // }
}
