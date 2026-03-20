#include "Renderer.hpp"

Renderer::Renderer(int width, int height, float scale)
  : window(sf::VideoMode(width, height), "N-Body Simulator"),
    scale(scale), centerX(width / 2.0f), centerY(height / 2.0f),
    maxTrailLength(400) {

  window.setFramerateLimit(60);

  colors = {
    sf::Color(255, 100, 100), // Red
    sf::Color(100, 255, 100), // Green
    sf::Color(100, 100, 255), // Blue
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta
  };
}

bool Renderer::isOpen() const {
  return window.isOpen();
}

void Renderer::handleEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

void Renderer::render(const Simulator &sim) {
  window.clear(sf::Color(10, 10, 15));
  const auto& bodies = sim.getBodies();

  if (trails.size() < bodies.size()) {
    trails.resize(bodies.size());
  }

  for (std::size_t i = 0; i < bodies.size(); ++i) {

    // Compute position
    float screenX = centerX + static_cast<float>(bodies[i].position.x / scale);
    float screenY = centerY + static_cast<float>(bodies[i].position.y / scale);
    sf::Vector2f currentPos(screenX, screenY);

    // Update trail
    trails[i].push_back(currentPos);
    if (trails[i].size() > maxTrailLength) {
      trails[i].pop_front();
    }

    // Draw trail
    sf::VertexArray trailLine(sf::LineStrip, trails[i].size());
    sf::Color baseColor = colors[i % colors.size()];

    for (std::size_t j = 0; j < trails[i].size(); ++j) {
      trailLine[j].position = trails[i][j];
      sf::Color trailColor = baseColor;
      trailColor.a = static_cast<sf::Uint8>((j * 255) / trails[i].size());
      trailLine[j].color = trailColor;
    }
    window.draw(trailLine);

    //  Draw Body
    sf::CircleShape shape(6.f);
    shape.setFillColor(baseColor);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(currentPos);

    window.draw(shape);

  }

  window.display();

}




