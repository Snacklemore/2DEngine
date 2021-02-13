//
// Created by root on 23.08.19.
//

#ifndef INC_2DENGINE_WINDOW_H
#define INC_2DENGINE_WINDOW_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class Window{

public:
    Window(const std::string& windowName);
    void Draw(const sf::Vertex * vertices, std::size_t vertexCount, sf::PrimitiveType type);
    void Update();
    void BeginDraw();
    void Draw(const sf::Drawable& drawable);
    void EndDraw();
    bool isOpen() const;
    sf::RenderWindow* getWindowHandle();
    sf::Vector2u GetCentre() const;
    const sf::View& GetView() const;
    void SetView(const sf::View& view);
    sf::FloatRect GetViewSpace() const;
    bool setGui(std::shared_ptr<tgui::GuiSFML> p_gui);

private:
    sf::RenderWindow window;
    std::shared_ptr<tgui::GuiSFML> gui;
};


#endif //INC_2DENGINE_WINDOW_H
