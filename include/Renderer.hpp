#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "Simulator.hpp"

class Renderer {
public:
  // Constructor
  Renderer(int width, int height, float scale);

  //
  bool isOpen() const;

  void handleEvents();

  void render(const Simulator& sim);

private:
  sf::RenderWindow window;
  float scale;
  float centerX;
  float centerY;

  std::size_t maxTrailLength;
  std::vector<std::deque<sf::Vector2f>> trails;
  std::vector<sf::Color> colors;

};