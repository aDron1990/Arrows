#pragma once

#include <kwee/kwee.h>

enum class ArrowType
{
    Wire = 1,
    DoubleWire = 2,
    Block = 3,
    Not = 4,
    And = 5,
    TreeWire = 6,
    Lever = 7
};

std::string TypeToString(ArrowType type);
ArrowType StringToType(std::string str);

class Direction
{
private:
    int degrees = 0;

public:
    Direction() {}

    Direction(int dr) { degrees = dr * 90; };

    void rotate_plus()
    {
        degrees += 90;
        if (degrees == 360) degrees = 0;
    }

    void rotate_minus()
    {
        degrees -= 90;
        if (degrees == -90) degrees = 270;
    }

    int getDegrees() { return degrees; }

    glm::ivec2 getGridOffset()
    {
        switch (degrees)
        {
            case 0: return glm::ivec2{0, 1};
            case 90: return glm::ivec2{-1, 0};
            case 180: return glm::ivec2{0, -1};
            case 270: return glm::ivec2{1, 0};
            default: throw;
        }
    }
};

std::string DirToString(Direction dir);
Direction StringToDir(std::string str);

class Grid;
class Arrow : public kwee::GameObject
{
    friend class GridSerializer;

private:
    Grid* grid_;
    bool state_;

    Direction dir_;
    ArrowType type_;

    std::shared_ptr<kwee::Texture> activeTexture_;
    std::shared_ptr<kwee::Texture> unactiveTexture_;

protected:
    void sendSignal(glm::ivec2 offset);

public:
    Arrow(Grid* grid, ArrowType type, Direction dir, std::string activeTextrureName, std::string unactiveTextrureName);
    virtual ~Arrow() = default;

    void setState(bool state);
    bool getState();

    virtual void setSignals(int sig) = 0;

    void rotate_plus();
    void rotate_minus();

    Direction getDir();
    ArrowType getType();

    virtual void action();
    virtual void onClick(){};
};
