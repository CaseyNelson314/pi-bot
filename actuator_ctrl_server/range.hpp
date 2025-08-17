#pragma once

template <typename T>
struct range
{
    T min;
    T max;

    T diff() const
    {
        return max - min;
    }
};
