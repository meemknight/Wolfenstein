#pragma once
#define PI 3.1415926f
#include <utility>

int getQuadrant(float);

std::pair<float, float> intersect(float angle, float x, float y, float m2, float n2);

std::pair<float, float> intersect(float m1, float n1, float m2, float n2);

float getDistance(float x1, float y1, float x2, float y2);