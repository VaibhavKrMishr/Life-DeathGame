#pragma once

#include "Grid.hpp"
#include "Camera.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Renderer {
public:
    Renderer();

    void render(sf::RenderWindow& window, const Grid& grid, const Camera& camera, bool drawGridLines);

    float getCellSize() const;
    void setCellSize(float size);

private:
    void updateCellVertices(const Grid& grid);
    void updateGridVertices(const Camera& camera, const sf::RenderWindow& window);

    float m_cellSize;
    sf::VertexArray m_cellVertices;
    sf::VertexArray m_gridVertices;
    
    // Store the last camera view to avoid regenerating grid lines if not needed
    sf::Vector2f m_lastCameraCenter;
    sf::Vector2f m_lastCameraSize;
};
