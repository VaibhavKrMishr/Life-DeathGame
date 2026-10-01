#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Simulation;
class Camera;
class Renderer;

// Holds the global application state that input can modify
struct AppState {
    bool isPaused = true;
    bool drawGridLines = true;
    bool isRunning = true;
    float simulationSpeed = 10.0f; // Generations per second
    bool requestStep = false;
};

class Input {
public:
    Input(Simulation& simulation, Camera& camera, Renderer& renderer, AppState& appState);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update(const sf::RenderWindow& window);

private:
    void handleKeyPress(const sf::Event::KeyEvent& keyEvent);
    
    Simulation& m_simulation;
    Camera& m_camera;
    Renderer& m_renderer;
    AppState& m_appState;

    bool m_isPanning = false;
    bool m_isDrawing = false;
    bool m_isErasing = false;
    sf::Vector2i m_lastMousePos;
};
