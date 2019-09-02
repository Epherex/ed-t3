#include "building.h"
#include <stdlib.h>

typedef struct building_t {
    double x;
    double y;
    double w;
    double h;
    double num;
} *BuildingPtr;

Building Building_Create(double x, double y, double w, double h, double num) {
    BuildingPtr building = malloc(sizeof(struct building_t));
    building->x = x;
    building->y = y;
    building->w = w;
    building->h = h;
    building->num = num;
    return building;
}

#include <stdio.h>

Segment *Building_PutSegments(Building buildingVoid, Segment *vector, double x, double y) {
    BuildingPtr b = (BuildingPtr) buildingVoid;
    
    Segment southSeg = Segment_CreateFromCoords(b->x, b->y, b->x + b->w, b->y, x, y);
    *(vector++) = southSeg;

    Segment northSeg = Segment_CreateFromCoords(b->x, b->y + b->h, b->x + b->w, b->y + b->h, x, y);
    *(vector++) = northSeg;

    Segment eastSeg = Segment_CreateFromCoords(b->x, b->y, b->x, b->y + b->h, x, y);
    *(vector++) = eastSeg;

    //double xinter = Segment_CheckXIntersection(eastSeg, y);

    Segment westSeg = Segment_CreateFromCoords(b->x + b->w, b->y, b->x + b->w, b->y + b->h, x, y);
    *(vector++) = westSeg;

    // Intersecção com a reta
    if (b->x < x && y >= b->y && y <= b->y + b->h) {
        // Segmento leste
        double distance = fabs(b->x - x);
        Point pAbove = Point_Create(b->x, y, eastSeg, -PI, distance);
        Point oldPStart = Segment_GetPStart(eastSeg);
        Point oldPEnd = Segment_GetPEnd(eastSeg);
        Segment_SetPStart(eastSeg, pAbove);
        Segment_SetPEnd(eastSeg, oldPStart);
        Point_SetStarting(pAbove, true);
        Point_SetStarting(oldPStart, false);

        Point pBelow = Point_Create(b->x, y, NULL, PI, distance);
        Segment newSeg = Segment_Create(oldPEnd, pBelow);
        Point_SetSegment(pBelow, newSeg);
        Point_SetSegment(oldPEnd, newSeg);
        Point_SetStarting(oldPEnd, true);
        Point_SetStarting(pBelow, false);
        *(vector++) = newSeg;

        // Segmento oeste
        distance = fabs(b->x + b->w - x);
        pAbove = Point_Create(b->x + b->w, y, westSeg, -PI, distance);
        oldPStart = Segment_GetPStart(westSeg);
        oldPEnd = Segment_GetPEnd(westSeg);
        Segment_SetPStart(westSeg, pAbove);
        Segment_SetPEnd(westSeg, oldPStart);
        Point_SetStarting(pAbove, true);
        Point_SetStarting(oldPStart, false);

        pBelow = Point_Create(b->x + b->w, y, NULL, PI, distance);
        newSeg = Segment_Create(oldPEnd, pBelow);
        Point_SetSegment(pBelow, newSeg);
        Point_SetSegment(oldPEnd, newSeg);
        Point_SetStarting(oldPEnd, true);
        Point_SetStarting(pBelow, false);
        *(vector++) = newSeg;
    }

    return vector;
}

double Building_GetX(Building buildingVoid) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    return building->x;
}

double Building_GetY(Building buildingVoid) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    return building->y;
}

double Building_GetW(Building buildingVoid) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    return building->w;
}

double Building_GetH(Building buildingVoid) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    return building->h;
}

double Building_GetNum(Building buildingVoid) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    return building->num;
}

void Building_SetX(Building buildingVoid, double x) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    building->x = x;
}

void Building_SetY(Building buildingVoid, double y) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    building->y = y;
}

void Building_SetW(Building buildingVoid, double w) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    building->w = w;
}

void Building_SetH(Building buildingVoid, double h) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    building->h = h;
}

void Building_SetNum(Building buildingVoid, double num) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    building->num = num;
}

void Building_Destroy(Building buildingVoid) {
    BuildingPtr building = (BuildingPtr) buildingVoid;
    free(building);
}
