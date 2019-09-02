#include "wall.h"

#include <stdlib.h>

typedef struct wall_t {
    double x1;
    double y1;
    double x2;
    double y2;
} *WallPtr;

Wall Wall_Create(double x1, double y1, double x2, double y2) {
    WallPtr wall = malloc(sizeof(struct wall_t));
    wall->x1 = x1;
    wall->y1 = y1;
    wall->x2 = x2;
    wall->y2 = y2;
    return wall;
}

#include <stdio.h>

Segment *Wall_PutSegments(Wall wallVoid, Segment *vector, double x, double y) {
    WallPtr wall = (WallPtr) wallVoid;
    Segment seg = Segment_CreateFromCoords(wall->x1, wall->y1, wall->x2, wall->y2, x, y);
    (*vector++) = seg;

    double xinter = Segment_CheckXIntersection(seg, y);
    if (xinter <= x && xinter <= max(wall->x1, wall->x2) && xinter >= min(wall->x1, wall->x2)) {
        double distance = fabs(xinter - x);
        Point pAbove = Point_Create(xinter, y, seg, -PI, distance);
        Point oldPStart = Segment_GetPStart(seg);
        Point oldPEnd = Segment_GetPEnd(seg);
        Segment_SetPStart(seg, pAbove);
        Segment_SetPEnd(seg, oldPStart);
        Point_SetStarting(pAbove, true);
        Point_SetStarting(oldPStart, false);
        //printf("----------- %.2lf %.2lf\n", Point_GetX(oldPStart), Point_GetY(oldPStart));

        Point pBelow = Point_Create(xinter, y, NULL, PI, distance);
        Segment newSeg = Segment_Create(oldPEnd, pBelow);
        Point_SetSegment(pBelow, newSeg);
        Point_SetSegment(oldPEnd, newSeg);
        Point_SetStarting(oldPEnd, true);
        Point_SetStarting(pBelow, false);
        *(vector++) = newSeg;
    }

    return vector;
}

double Wall_GetX1(Wall wallVoid) {
    WallPtr wall = (WallPtr) wallVoid;
    return wall->x1;
}

double Wall_GetY1(Wall wallVoid) {
    WallPtr wall = (WallPtr) wallVoid;
    return wall->y1;
}

double Wall_GetX2(Wall wallVoid) {
    WallPtr wall = (WallPtr) wallVoid;
    return wall->x2;
}

double Wall_GetY2(Wall wallVoid) {
    WallPtr wall = (WallPtr) wallVoid;
    return wall->y2;
}

void Wall_SetX1(Wall wallVoid, double x1) {
    WallPtr wall = (WallPtr) wallVoid;
    wall->x1 = x1;
}

void Wall_SetY1(Wall wallVoid, double y1) {
    WallPtr wall = (WallPtr) wallVoid;
    wall->y1 = y1;
}

void Wall_SetX2(Wall wallVoid, double x2) {
    WallPtr wall = (WallPtr) wallVoid;
    wall->x2 = x2;
}

void Wall_SetY2(Wall wallVoid, double y2) {
    WallPtr wall = (WallPtr) wallVoid;
    wall->y2 = y2;
}

void Wall_Destroy(Wall wallVoid) {
    WallPtr wall = (WallPtr) wallVoid;
    free(wall);
}
