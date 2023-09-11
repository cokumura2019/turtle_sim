#include <cmath>

struct vector2
{
    float x;
    float y;

    vector2 operator-(const vector2 other) const
    {
        return {x- other.x, y - other.y};
    }

    vector2 operator+(const vector2 other) const
    {
        return {other.x + x, other.y + y};
    }

    bool operator==(const vector2 other) const
    {
        return other.x==x && other.y == y;
    }

    vector2& operator=(const vector2& other)
    {
        x = other.x;
        y=other.y;
        return *this;
    }

    double get_angle() const
    {
        return atan2(y, x);
    }

    double get_magnitude() const
    {
        return sqrt(x * x + y * y);
    }
};



