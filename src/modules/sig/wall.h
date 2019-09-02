#ifndef WALL_H
#define WALL_H

#include <stdlib.h>
#include "../aux/segment.h"
#include "../aux/point.h"
#include "../sig/geometry.h"

typedef void *Wall;

Wall Wall_Create(double x1, double y1, double x2, double y2);

Segment *Wall_PutSegments(Wall wallVoid, Segment *vector, double x, double y);

double Wall_GetX1(Wall wall);

double Wall_GetY1(Wall wall);

double Wall_GetX2(Wall wall);

double Wall_GetY2(Wall wall);

void Wall_SetX1(Wall wall, double x1);

void Wall_SetY1(Wall wall, double y1);

void Wall_SetX2(Wall wall, double x2);

void Wall_SetY2(Wall wall, double y2);

void Wall_Destroy(Wall wall);

#endif
