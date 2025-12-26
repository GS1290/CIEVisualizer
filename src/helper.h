#ifndef HELPER_H_
#define HELPER_H_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"

Mesh* CreateRGBCube(int gridSize);
Mesh CreateRGBFace(Vector3 *vertices, Color *colors, int gridSize);
Mesh CreateColoredSquare(int gridSize);
Mesh CreateColoredTriangle();


#endif