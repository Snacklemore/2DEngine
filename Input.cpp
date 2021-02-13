//
// Created by root on 27.08.19.
//

#include <SFML/Window/Keyboard.hpp>
#include "Input.h"

void Input::Update()
{
    if (isLocked)
        return;
    lastFrameKeys.SetMask(thisFrameKeys);

    thisFrameKeys.SetBit((int)Key::Left,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
                                 (sf::Keyboard::isKeyPressed(sf::Keyboard::A)));

    thisFrameKeys.SetBit((int)Key::Right,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
                                 (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));

    thisFrameKeys.SetBit((int)Key::Up,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
                                 (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));

    thisFrameKeys.SetBit((int)Key::Down,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
                                 (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));
    thisFrameKeys.SetBit((int)Key::Esc,
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
    thisFrameKeys.SetBit((int) Key::U,
            sf::Keyboard::isKeyPressed(sf::Keyboard::U));
    thisFrameKeys.SetBit((int) Key::O,
            sf::Keyboard::isKeyPressed(sf::Keyboard::O));
    thisFrameKeys.SetBit((int)Key::E,sf::Keyboard::isKeyPressed(sf::Keyboard::E));
    thisFrameKeys.SetBit((int)Key::F,sf::Keyboard::isKeyPressed(sf::Keyboard::F));

}
//true if key=keycode is pressed
bool Input::IsKeyPressed(Input::Key keycode) {
    return thisFrameKeys.GetBit((int) keycode);
}
//ture if the key was pressed (registered as pressed this frame but not previous)
bool Input::IsKeyDown(Input::Key keycode) {
    bool lastFrame = lastFrameKeys.GetBit((int) keycode);
    bool thisFrame = thisFrameKeys.GetBit((int) keycode);
    return  thisFrame && !lastFrame;
}
// true if key was just released (registered as pressed last frame but not this one)
bool Input::IsKeyUp(Input::Key keycode) {
    bool lastFrame = lastFrameKeys.GetBit((int) keycode);
    bool thisFrame = thisFrameKeys.GetBit((int) keycode);

    return !thisFrame && lastFrame;
}

Input::Input():isLocked(false) {

}

void Input::Lock() {
    isLocked = true;

}

void Input::Unlock() {
    isLocked = false;

}
