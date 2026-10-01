#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Input.hpp" // For AppState

class Simulation;

class Statistics {
public:
    Statistics();
    
    bool loadFont(const std::string& path);
    void update(const AppState& appState, const Simulation& simulation, float fps);
    void render(sf::RenderWindow& window);

private:
    sf::Font m_font;
    sf::Text m_text;
    bool m_fontLoaded;
};
