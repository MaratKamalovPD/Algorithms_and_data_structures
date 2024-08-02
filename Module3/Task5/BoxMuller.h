#ifndef BOXMULLER_H
#define BOXMULLER_H


#include <limits.h>
#include <random>
#include <cmath>

const float pi = 3.1415926535;

float RandomFloat();
std::pair<float, float> GetNormalRandPoint(); // ������� ��� �������� ����� (�������) � ������� �������������� ����� - �������.

#endif