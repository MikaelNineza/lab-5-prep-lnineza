#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS_LIMIT = 60;

// global tween function
std::function<float(float, float, float)> tween = [](float a, float b, float t) {
    return (1 - t) * a + t * b;
};

void handleInput(sf::Window& window, bool& shouldQuit) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            shouldQuit = true;
        }

        // ====== ====== ======
        // TODO: (Q2)
        //  implement key presses (1-9) that replace the tween function
        //  with different alternate tween functions.
        //  Functions can be from lecture or from https://easings.net/#
        // ====== ====== ======
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Num1) tween = [](float a, float b, float t) { // easeInSine
                t = 1 - std::cos((t * M_PI) / 2);
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num2) tween = [](float a, float b, float t) { // easeInQuart
                t = t * t * t * t; 
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num3) tween = [](float a, float b, float t) { // easeInOutQuad
                t = t < 0.5 ? t * t * 2 : 1 - (((t * (-2) + 2) * t) / 2);
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num4) tween = [](float a, float b, float t) { // easeOutCirc
                t = std::sqrt(1 - std::pow(t - 1, 2));
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num5) tween = [](float a, float b, float t) { // easeInCirc
                t = 1 - std::sqrt(1 - std::pow(t, 2));
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num6) tween = [](float a, float b, float t) { // easeInQuint
                t = t * t * t * t * t;
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num7) tween = [](float a, float b, float t) { // easeInExpo
                t = t == 0 ? 0 : std::pow(2, 10 * t - 10); 
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num8) tween = [](float a, float b, float t) { // easeInOutSine
                t = -(std::cos(M_PI * t) - 1) / 2; 
                return (1 - t) * a + t * b;
            };
            else if (keyPressed->code == sf::Keyboard::Key::Num9) tween = [](float a, float b, float t) { // easeOutCubic
                t = 1 - std::pow(1 - t, 3);
                return (1 - t) * a + t * b;
            };
        }
    }
}

void render(sf::RenderWindow& window) {
    // Clear with blue background (sky)
    window.clear(sf::Color::Black);
    // ====== ====== ======
    // TODO: (Q1) Draw circle that moves between
    // the left/right half of the screen.
    // Movement should be governed by the tween function.
    // ====== ====== ======
    sf::CircleShape circle(15.0F);
    static float time(0);
    circle.setPosition({tween(30.0F, WINDOW_WIDTH - 30.0F, time++ / FPS_LIMIT), WINDOW_HEIGHT / 3.0F});
    if (time >= FPS_LIMIT) time = 0;
    window.draw(circle);


    // ====== ====== ======
    // TODO: (Q3) Draw tween function graph with a dot
    // on the current portion of the curve
    // ====== ====== ======

    window.display();
}

int main() {
    sf::RenderWindow window;

    try {
        // Initialize window
        window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tween");
        window.setFramerateLimit(FPS_LIMIT);
        // Prevent key repeats.
        window.setKeyRepeatEnabled(false);

        bool shouldQuit = false;
        // Main game loop
        while (window.isOpen()) {
            handleInput(window, shouldQuit);
            if (shouldQuit) {
                break;
            }
            render(window);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
