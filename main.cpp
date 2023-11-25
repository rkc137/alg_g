#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <thread>

#include "obj.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "graph", sf::Style::Fullscreen);
    sf::Vector2u past_window_size = window.getSize();

    int objs_count = 120;
    obj::set_shapes(objs_count, window.getSize().x, window.getSize().y);
    std::vector<obj> vec;
    vec.reserve(objs_count);
    for(int i = 1; i <= objs_count; i++)
        vec.emplace_back(i);


    std::random_shuffle(vec.begin(), vec.end());
    for(int i = 0; i < objs_count; i++)
            vec[i].set_pos(i);

    int i = 0, j = 0;
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
            }
        }    

        if(i < objs_count - 1)
        {
            if(j < objs_count - i - 1)
            {
                if(vec[j] > vec[j + 1])
                {
                    vec[j].set_pos(j + 1);
                    vec[j + 1].set_pos(j);
                    std::swap(vec[j], vec[j + 1]);
                }
                j++;    
            }
            else
            {
                j = 0;
                i++;
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds(500));

        for(auto &i: vec)
            window.draw(i);
        window.display();
        window.clear();
    }
    return 0;
}