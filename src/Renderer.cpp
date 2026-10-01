#include "Renderer.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cmath>

Renderer::Renderer() : m_cellSize(10.0f) {
    m_cellVertices.setPrimitiveType(sf::Quads);
    m_gridVertices.setPrimitiveType(sf::Lines);
}

void Renderer::render(sf::RenderWindow& window, const Grid& grid, const Camera& camera, bool drawGridLines) {
    window.setView(camera.getView());
    
    updateCellVertices(grid);
    window.draw(m_cellVertices);
    
    if (drawGridLines) {
        updateGridVertices(camera, window);
        window.draw(m_gridVertices);
    }
}

void Renderer::updateCellVertices(const Grid& grid) {
    auto aliveCells = grid.getAliveCells();
    m_cellVertices.resize(aliveCells.size() * 4);
    
    sf::Color aliveColor = sf::Color::White;
    // We could add highlighted changes here later by comparing with previous state
    
    std::size_t index = 0;
    for (const auto& cell : aliveCells) {
        float x = cell.x * m_cellSize;
        float y = cell.y * m_cellSize;
        
        m_cellVertices[index].position = sf::Vector2f(x, y);
        m_cellVertices[index + 1].position = sf::Vector2f(x + m_cellSize, y);
        m_cellVertices[index + 2].position = sf::Vector2f(x + m_cellSize, y + m_cellSize);
        m_cellVertices[index + 3].position = sf::Vector2f(x, y + m_cellSize);
        
        m_cellVertices[index].color = aliveColor;
        m_cellVertices[index + 1].color = aliveColor;
        m_cellVertices[index + 2].color = aliveColor;
        m_cellVertices[index + 3].color = aliveColor;
        
        index += 4;
    }
}

void Renderer::updateGridVertices(const Camera& camera, const sf::RenderWindow& window) {
    sf::View view = camera.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();
    
    // Only update if camera changed significantly
    if (center == m_lastCameraCenter && size == m_lastCameraSize) {
        return;
    }
    
    m_lastCameraCenter = center;
    m_lastCameraSize = size;
    
    m_gridVertices.clear();
    
    // Don't draw grid if it's too zoomed out (prevent Moire patterns and lag)
    if (m_cellSize * (window.getSize().x / size.x) < 4.0f) {
        return;
    }
    
    float left = center.x - size.x / 2.0f;
    float right = center.x + size.x / 2.0f;
    float top = center.y - size.y / 2.0f;
    float bottom = center.y + size.y / 2.0f;
    
    int startX = static_cast<int>(std::floor(left / m_cellSize));
    int endX = static_cast<int>(std::ceil(right / m_cellSize));
    int startY = static_cast<int>(std::floor(top / m_cellSize));
    int endY = static_cast<int>(std::ceil(bottom / m_cellSize));
    
    sf::Color gridColor(50, 50, 50, 100); // Dark gray, semi-transparent
    
    for (int x = startX; x <= endX; ++x) {
        m_gridVertices.append(sf::Vertex(sf::Vector2f(x * m_cellSize, top), gridColor));
        m_gridVertices.append(sf::Vertex(sf::Vector2f(x * m_cellSize, bottom), gridColor));
    }
    
    for (int y = startY; y <= endY; ++y) {
        m_gridVertices.append(sf::Vertex(sf::Vector2f(left, y * m_cellSize), gridColor));
        m_gridVertices.append(sf::Vertex(sf::Vector2f(right, y * m_cellSize), gridColor));
    }
}

float Renderer::getCellSize() const {
    return m_cellSize;
}

void Renderer::setCellSize(float size) {
    if (size > 0.1f) {
        m_cellSize = size;
        m_lastCameraSize = sf::Vector2f(0, 0); // Force grid redraw
    }
}
