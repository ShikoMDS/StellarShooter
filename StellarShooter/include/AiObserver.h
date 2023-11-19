#pragma once
#include <SFML/System/Vector2.hpp>

class AiObserver {
public:
    virtual ~AiObserver() = default;
    virtual bool canMoveTo(const sf::Vector2f& newPosition) const = 0;
};
