#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class obj : public sf::RectangleShape
{
public:
    obj(int v) : sf::RectangleShape(sf::Vector2f(objs_width, objs_height * v)), value(v)
    {
        setPosition(sf::Vector2f(v * objs_width, 0));
        setFillColor(sf::Color(v * 10, 100, 100));
    }
    static void set_shapes(int objs_count, int width, int height)
    {
        objs_width = width / objs_count;
        objs_height = height / objs_count;
    }
private:
    inline static int objs_width = 10, objs_height = 10;
    int value;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "graph");

    int objs_count = 10;
    obj::set_shapes(objs_count, window.getSize().x, window.getSize().y);

    std::vector<obj> vec;
    vec.reserve(objs_count);
    for(int i = 0; i < objs_count; i++)
        vec.emplace_back(i);


    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                return 0;
            case sf::Event::Resized:
                
            default:
                break;
            }
        }
        
        for(auto &i: vec)
            window.draw(i);
        window.display();
        window.clear();
    }

    return 0;
}