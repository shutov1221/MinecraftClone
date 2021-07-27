#pragma once
#include <vector>
#include <algorithm>

typedef unsigned int uint;

class Keyboard
{
public:
	Keyboard() = default;
    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);
    bool JustKeyPressed(int key);
    void SetKeyPressed(int key);
    void SetKeyReleased(int key);
    void frameHandler(uint* _frames, uint current);

private:
    std::vector<int> _Keys;
    uint* frames;
    uint current;
};

