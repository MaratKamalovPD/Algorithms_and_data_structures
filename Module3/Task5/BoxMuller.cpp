#include "BoxMuller.h"


float RandomFloat()
{
    return (float)rand() / RAND_MAX;
}

std::pair<float, float> GetNormalRandPoint() // функция для создания точки (вершины) с помощью преобразования Бокса - Мюллера.
{
    float z = RandomFloat();
    float f = RandomFloat();

    std::pair<float, float> point;

    float x = cos(2 * pi * f) * sqrt(-2 * log(z));
    float y = sin(2 * pi * f) * sqrt(-2 * log(z));
    point.first = x;
    point.second = y;

    return point;
}