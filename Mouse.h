#pragma once
#include <vector>
#include <algorithm>

enum MouseButton {
    RIGHT,
    LEFT,
    MIDDLE,
    BACK,
    FORWARD
};

class Mouse
{
public:
    Mouse() = default;
    bool IsKeyPressed(MouseButton key);
    void SetKeyPressed(MouseButton key);
    void SetKeyReleased(MouseButton key);

    static double x;
    static double y;
    static double dx;
    static double dy;

private:
    std::vector<MouseButton> _Keys;
};

