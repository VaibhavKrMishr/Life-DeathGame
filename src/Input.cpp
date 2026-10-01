#include "Input.hpp"
#include "Simulation.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Pattern.hpp"
#include "Serialization.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>

Input::Input(Simulation& simulation, Camera& camera, Renderer& renderer, AppState& appState)
    : m_simulation(simulation), m_camera(camera), m_renderer(renderer), m_appState(appState) {}

void Input::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        m_appState.isRunning = false;
    }
    else if (event.type == sf::Event::KeyPressed) {
        handleKeyPress(event.key);
    }
    else if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            float delta = event.mouseWheelScroll.delta;
            if (delta > 0) {
                m_camera.zoom(0.9f);
            } else if (delta < 0) {
                m_camera.zoom(1.1f);
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Middle) {
            m_isPanning = true;
            m_lastMousePos = sf::Mouse::getPosition(window);
        }
        else if (event.mouseButton.button == sf::Mouse::Left) {
            m_isDrawing = true;
            
            // Toggle single cell on click
            sf::Vector2f worldPos = m_camera.screenToWorld(sf::Mouse::getPosition(window), window);
            int32_t gridX = static_cast<int32_t>(std::floor(worldPos.x / m_renderer.getCellSize()));
            int32_t gridY = static_cast<int32_t>(std::floor(worldPos.y / m_renderer.getCellSize()));
            m_simulation.getGrid().toggleCell(gridX, gridY);
        }
        else if (event.mouseButton.button == sf::Mouse::Right) {
            m_isErasing = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Middle) {
            m_isPanning = false;
        }
        else if (event.mouseButton.button == sf::Mouse::Left) {
            m_isDrawing = false;
        }
        else if (event.mouseButton.button == sf::Mouse::Right) {
            m_isErasing = false;
        }
    }
}

void Input::update(const sf::RenderWindow& window) {
    if (!window.hasFocus()) return;

    sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
    
    if (m_isPanning) {
        sf::Vector2f delta = m_camera.screenToWorld(m_lastMousePos, window) - m_camera.screenToWorld(currentMousePos, window);
        m_camera.move(delta);
        m_lastMousePos = currentMousePos; // Update for continuous panning
    }
    else if (m_isDrawing || m_isErasing) {
        sf::Vector2f worldPos = m_camera.screenToWorld(currentMousePos, window);
        int32_t gridX = static_cast<int32_t>(std::floor(worldPos.x / m_renderer.getCellSize()));
        int32_t gridY = static_cast<int32_t>(std::floor(worldPos.y / m_renderer.getCellSize()));
        
        if (m_isDrawing) {
            m_simulation.getGrid().setCell(gridX, gridY, true);
        } else if (m_isErasing) {
            m_simulation.getGrid().setCell(gridX, gridY, false);
        }
    }
    
    // Always track last mouse pos to prevent panning jumps
    if (!m_isPanning) {
        m_lastMousePos = currentMousePos;
    }
}

void Input::handleKeyPress(const sf::Event::KeyEvent& keyEvent) {
    switch (keyEvent.code) {
        case sf::Keyboard::Space:
            m_appState.isPaused = !m_appState.isPaused;
            break;
        case sf::Keyboard::Right:
            m_appState.requestStep = true;
            m_appState.isPaused = true;
            break;
        case sf::Keyboard::C:
            m_simulation.reset();
            break;
        case sf::Keyboard::G:
            m_appState.drawGridLines = !m_appState.drawGridLines;
            break;
        case sf::Keyboard::R:
            // Randomize grid logic could be here, or triggered via a state flag
            // For now, let's implement a quick randomizer
            m_simulation.reset();
            for (int x = 0; x < 100; ++x) {
                for (int y = 0; y < 100; ++y) {
                    if (rand() % 4 == 0) {
                        m_simulation.getGrid().setCell(x, y, true);
                    }
                }
            }
            break;
        case sf::Keyboard::Escape:
            m_appState.isRunning = false;
            break;
        case sf::Keyboard::S:
            Serialization::save(m_simulation.getGrid(), "save.json");
            break;
        case sf::Keyboard::L:
            Serialization::load(m_simulation.getGrid(), "save.json");
            break;
        case sf::Keyboard::F:
            // Fullscreen toggle could be handled here or in main
            break;
        case sf::Keyboard::Num1:
        case sf::Keyboard::Num2:
        case sf::Keyboard::Num3:
        case sf::Keyboard::Num4: {
            // We need a reference to the window for screenToWorld, let's just place it at 0,0 for now, or keep track of last world pos
            // Wait, we removed window from handleKeyPress. 
            // So we can place it at the center of the camera.
            sf::Vector2f center = m_camera.getView().getCenter();
            int32_t gridX = static_cast<int32_t>(center.x / m_renderer.getCellSize());
            int32_t gridY = static_cast<int32_t>(center.y / m_renderer.getCellSize());
            
            Pattern::Type type = Pattern::Type::Glider;
            if (keyEvent.code == sf::Keyboard::Num2) type = Pattern::Type::GosperGliderGun;
            if (keyEvent.code == sf::Keyboard::Num3) type = Pattern::Type::Pulsar;
            if (keyEvent.code == sf::Keyboard::Num4) type = Pattern::Type::LightweightSpaceship;
            
            Pattern::place(m_simulation.getGrid(), gridX, gridY, Pattern::get(type));
            break;
        }
        default:
            break;
    }
}
