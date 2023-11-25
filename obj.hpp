#pragma once

#include <SFML/Graphics.hpp>

class obj : public sf::RectangleShape
{
public:
    obj(int v) : sf::RectangleShape(sf::Vector2f(objs_width, -(objs_height * v))), value(v)
    {
        setFillColor(sf::Color(v * 5, v * 3, 100));
    }
    void set_pos(int x)
    {
        setPosition(sf::Vector2f(x * objs_width, window_height));
    }

    bool operator<(const obj &r) const
    {
        if (value != r.value)
            return value < r.value;
        return value < r.value;
    }
    bool operator>(const obj &r) const
    {
        if (value != r.value)
            return value > r.value;
        return value > r.value;
    }

    static void set_shapes(int objs_count, int width, int height)
    {
        window_height = height;
        objs_width = width / objs_count;
        objs_height = height / objs_count;
    }
private:
    inline static int objs_width, objs_height, window_height;
    int value;
};