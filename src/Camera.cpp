#include "Camera.hpp"
#include <algorithm>

Camera::Camera(const sf::Vector2f& windowSize)
    : m_zoomLevel(1.0f) {
    m_view.setSize(windowSize);
    m_view.setCenter(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

void Camera::setSize(const sf::Vector2f& size) {
    m_view.setSize(size);
    m_view.zoom(m_zoomLevel); // Reapply current zoom level
}

void Camera::zoom(float factor) {
    float newZoom = m_zoomLevel * factor;
    if (newZoom >= MIN_ZOOM && newZoom <= MAX_ZOOM) {
        m_zoomLevel = newZoom;
        m_view.zoom(factor);
    }
}

void Camera::move(const sf::Vector2f& offset) {
    m_view.move(offset);
}

void Camera::setCenter(const sf::Vector2f& center) {
    m_view.setCenter(center);
}

void Camera::reset(const sf::Vector2f& windowSize) {
    m_zoomLevel = 1.0f;
    m_view.setSize(windowSize);
    m_view.setCenter(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

const sf::View& Camera::getView() const {
    return m_view;
}

sf::Vector2f Camera::screenToWorld(const sf::Vector2i& pixelPos, const sf::RenderWindow& window) const {
    return window.mapPixelToCoords(pixelPos, m_view);
}
