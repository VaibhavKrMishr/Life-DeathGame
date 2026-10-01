#include <SFML/Graphics.hpp>
#include "Simulation.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Statistics.hpp"
#include <iostream>

int main() {
    // 1. Setup Window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Conway's Game of Life");
    window.setFramerateLimit(144); // High FPS for smooth rendering/panning

    // 2. Setup Core Components
    int32_t gridWidth = 1000;
    int32_t gridHeight = 1000;
    Simulation simulation(gridWidth, gridHeight);
    
    // Default to sparse mode for infinite universe support and performance
    simulation.setSparseMode(true);
    
    Camera camera(sf::Vector2f(window.getSize().x, window.getSize().y));
    Renderer renderer;
    
    AppState appState;
    Input input(simulation, camera, renderer, appState);

    Statistics stats;
    if (!stats.loadFont("assets/Roboto-Regular.ttf")) {
        std::cerr << "Failed to load font from assets/Roboto-Regular.ttf" << std::endl;
    }

    // 3. Timing and Loop
    sf::Clock updateClock;
    sf::Clock renderClock;
    sf::Clock fpsClock;
    int frameCount = 0;
    float currentFps = 0.0f;

    while (appState.isRunning && window.isOpen()) {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                appState.isRunning = false;
            }
            input.handleEvent(event, window);
        }

        // Continuous input (panning, drawing)
        input.update(window);

        // Simulation Update
        float updateInterval = 1.0f / appState.simulationSpeed;
        if ((!appState.isPaused && updateClock.getElapsedTime().asSeconds() >= updateInterval) || appState.requestStep) {
            simulation.update();
            updateClock.restart();
            appState.requestStep = false;
        }

        // Rendering
        window.clear(sf::Color(30, 30, 30)); // Dark background
        
        renderer.render(window, simulation.getGrid(), camera, appState.drawGridLines);
        
        // Calculate FPS
        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            currentFps = static_cast<float>(frameCount) / fpsClock.restart().asSeconds();
            frameCount = 0;
        }

        stats.update(appState, simulation, currentFps);
        stats.render(window);
        
        window.display();
    }

    window.close();
    return 0;
}
