#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm> 
#include <cmath> 
#include <ctime> 

constexpr float PI = 3.14159265f;

static void displayArray(sf::RenderWindow& window, std::vector<int>& arr, const std::string& label, std::pair<int, int> swapIndices) {
    window.clear(sf::Color::Black);

    sf::Font font;
    font.loadFromFile("arialmt.ttf");

    sf::Text labelText;
    labelText.setFont(font);
    labelText.setCharacterSize(20);
    labelText.setString(label);
    labelText.setFillColor(sf::Color::White);
    labelText.setStyle(sf::Text::Bold);
    labelText.setPosition((window.getSize().x - labelText.getLocalBounds().width) / 2.f, 10.f);

    window.draw(labelText);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    float startX = (window.getSize().x - arr.size() * 40) / 2.0f; 
    float startY = 100.0f; 
    float offsetX = 40.0f; 
    float offsetY = 30.0f; 
    float arrowSize = 8.0f; 

    for (size_t i = 0; i < arr.size(); i++) {
        text.setString(std::to_string(arr[i]));
        text.setPosition(startX + i * offsetX, startY);
        window.draw(text);
    }

    if (swapIndices.first != -1 && swapIndices.second != -1) {
        float x1 = startX + swapIndices.first * offsetX + offsetX / 2;
        float x2 = startX + swapIndices.second * offsetX + offsetX / 2;

        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x1, startY);
        line[1].position = sf::Vector2f(x2, startY);

        float angle = atan2(0, x2 - x1);

        sf::ConvexShape arrow1;
        arrow1.setPointCount(3);
        arrow1.setPoint(0, sf::Vector2f(x1, startY));
        arrow1.setPoint(1, sf::Vector2f(x1 + arrowSize * cos(angle - PI / 6), startY + arrowSize * sin(angle - PI / 6)));
        arrow1.setPoint(2, sf::Vector2f(x1 + arrowSize * cos(angle + PI / 6), startY + arrowSize * sin(angle + PI / 6)));
        arrow1.setFillColor(sf::Color::Red);

        sf::ConvexShape arrow2;
        arrow2.setPointCount(3);
        arrow2.setPoint(0, sf::Vector2f(x2, startY));
        arrow2.setPoint(1, sf::Vector2f(x2 - arrowSize * cos(angle - PI / 6), startY - arrowSize * sin(angle - PI / 6)));
        arrow2.setPoint(2, sf::Vector2f(x2 - arrowSize * cos(angle + PI / 6), startY - arrowSize * sin(angle + PI / 6)));
        arrow2.setFillColor(sf::Color::Red);

        window.draw(line);
        window.draw(arrow1);
        window.draw(arrow2);
    }

    window.display();
}

static void quickSort(std::vector<int>& arr, int startIndex, int endIndex, sf::RenderWindow& window) {
    if (startIndex < endIndex) {
        int pivot = arr[endIndex];
        int i = startIndex - 1;

        for (int j = startIndex; j < endIndex; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
                displayArray(window, arr, "Sorting...", std::make_pair(i, j));
                sf::sleep(sf::milliseconds(1000));
            }
        }

        std::swap(arr[i + 1], arr[endIndex]);
        displayArray(window, arr, "Sorting...", std::make_pair(i + 1, endIndex));
        sf::sleep(sf::milliseconds(1000));

        quickSort(arr, startIndex, i, window);
        quickSort(arr, i + 2, endIndex, window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Quick Sort Visualization");
    window.setFramerateLimit(10);

    srand(time(0));

    int size = 10;
    std::vector<int> arr(size);

    for (int i = 0; i < size; i++) { arr[i] = rand() % 101 - 15; }

    displayArray(window, arr, "Before Sort", std::make_pair(-1, -1));
    sf::sleep(sf::seconds(1));

    quickSort(arr, 0, arr.size() - 1, window);

    displayArray(window, arr, "After Sort", std::make_pair(-1, -1));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
