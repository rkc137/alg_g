#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class obj : public sf::RectangleShape
{
public:
    obj(int v) : sf::RectangleShape(sf::Vector2f(objs_width, -(objs_height * v))), value(v)
    {
        setFillColor(sf::Color(v * 10, 100, 100));
    }
    
    void set_pos(int x)
    {
        setPosition(sf::Vector2f(x * objs_width, window_height));
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

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "graph");

    int objs_count = 50;
    obj::set_shapes(objs_count, window.getSize().x, window.getSize().y);

    std::vector<obj> vec;
    vec.reserve(objs_count);
    for(int i = 1; i <= objs_count; i++)
        vec.emplace_back(i);
    std::random_shuffle(vec.begin(), vec.end());
    for(int i = 0; i < objs_count; i++)
        vec[i].set_pos(i);

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
                break;
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