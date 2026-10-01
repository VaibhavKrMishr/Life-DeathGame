#include "Statistics.hpp"
#include "Simulation.hpp"
#include <sstream>
#include <iomanip>

Statistics::Statistics() : m_fontLoaded(false) {
    m_text.setCharacterSize(18);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.0f);
    m_text.setPosition(10.f, 10.f);
}

bool Statistics::loadFont(const std::string& path) {
    m_fontLoaded = m_font.loadFromFile(path);
    if (m_fontLoaded) {
        m_text.setFont(m_font);
    }
    return m_fontLoaded;
}

void Statistics::update(const AppState& appState, const Simulation& simulation, float fps) {
    if (!m_fontLoaded) return;

    std::stringstream ss;
    ss << "FPS: " << std::fixed << std::setprecision(1) << fps << "\n"
       << "Status: " << (appState.isPaused ? "Paused" : "Running") << "\n"
       << "Generation: " << simulation.getGeneration() << "\n"
       << "Alive Cells: " << simulation.getGrid().getAliveCount() << "\n"
       << "Simulation Speed: " << appState.simulationSpeed << " gen/s\n"
       << "Grid Mode: " << (simulation.isSparseMode() ? "Infinite (Sparse)" : "Finite (Dense)") << "\n\n"
       << "Controls:\n"
       << "Space: Play/Pause\n"
       << "Right Arrow: Step\n"
       << "Mouse Drag: Draw/Erase/Pan\n"
       << "Scroll: Zoom\n"
       << "1-4: Place Pattern\n"
       << "C: Clear, R: Randomize\n"
       << "S: Save, L: Load\n"
       << "G: Toggle Grid";

    m_text.setString(ss.str());
}

void Statistics::render(sf::RenderWindow& window) {
    if (m_fontLoaded) {
        // Render UI with default view so it stays on screen
        sf::View currentView = window.getView();
        window.setView(window.getDefaultView());
        window.draw(m_text);
        window.setView(currentView);
    }
}
