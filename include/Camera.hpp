#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize);

    void setSize(const sf::Vector2f& size);
    
    // Zoom in/out
    void zoom(float factor);
    
    // Panning
    void move(const sf::Vector2f& offset);
    
    // Center the camera
    void setCenter(const sf::Vector2f& center);
    
    // Reset to default
    void reset(const sf::Vector2f& windowSize);

    // Get the SFML view for rendering
    const sf::View& getView() const;

    // Convert pixel coordinates to world coordinates
    sf::Vector2f screenToWorld(const sf::Vector2i& pixelPos, const sf::RenderWindow& window) const;

private:
    sf::View m_view;
    float m_zoomLevel;
    const float MIN_ZOOM = 0.1f;
    const float MAX_ZOOM = 10.0f;
};
