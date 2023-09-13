#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <thread>

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

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 600), "graph");

    int objs_count = 200;
    obj::set_shapes(objs_count, window.getSize().x, window.getSize().y);
    std::vector<obj> vec;
    vec.reserve(objs_count);
    for(int i = 1; i <= objs_count; i++)
        vec.emplace_back(i);


    std::random_shuffle(vec.begin(), vec.end());
    for(int i = 0; i < objs_count; i++)
            vec[i].set_pos(i);
    
    std::thread sort_thread([&vec, objs_count](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (int i = 0; i < objs_count - 1; i++)
        {
            for (int j = 0; j < objs_count - i - 1; j++)
            {
                if (vec[j] > vec[j + 1])
                {
                    vec[j].set_pos(j + 1);
                    vec[j + 1].set_pos(j);
                    std::swap(vec[j], vec[j + 1]);
                    std::this_thread::sleep_for(std::chrono::microseconds(1000));
                }
            }
        }
    });

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                // sort_thread.join();
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