//
// Created by root on 23.08.19.
//

#include "Window.h"

Window::Window(const std::string &windowName)
: window(sf::VideoMode(800,600), windowName, sf::Style::None)
{
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);

}

void Window::Update() {
    sf::Event event;
    if(window.pollEvent(event))
    {
        gui->handleEvent(event);
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

}

void Window::BeginDraw() {
    window.clear(sf::Color::White);

}

void Window::Draw(const sf::Drawable &drawable) {
    window.draw(drawable);


}

void Window::EndDraw()
{
    window.display();

}

bool Window::isOpen() const {
    return  window.isOpen();
}

sf::Vector2u Window::GetCentre() const {
    sf::Vector2u size = window.getSize();

    return sf::Vector2u(size.x / 2 , size.y / 2);
}

sf::RenderWindow* Window::getWindowHandle() {
    return &window;
}

void Window::Draw(const sf::Vertex *vertices, std::size_t vertexCount, sf::PrimitiveType type) {
    window.draw(vertices,vertexCount,type);
}

const sf::View &Window::GetView() const {
    return window.getView();
}

void Window::SetView(const sf::View &view) {
    window.setView(view);
}

sf::FloatRect Window::GetViewSpace() const {
    const sf::View& view = GetView();
    const sf::Vector2f& viewCenter = view.getCenter();
    const sf::Vector2f& viewSize = view.getSize();
    sf::Vector2f viewSizeHalf(viewSize.x *0.5f,viewSize.y * 0.5f);
    sf::FloatRect viewSpace(viewCenter- viewSizeHalf, viewSize);
    return viewSpace;
}

bool Window::setGui(std::shared_ptr<tgui::GuiSFML> p_gui) {
    gui  = p_gui;
    return true;
}
