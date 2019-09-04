#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdlib.h>
#include <math.h>
#include "point.h"
#include "../sig/geometry.h"

typedef void *Point;

typedef void *Segment;

Segment Segment_Create(Point pStart, Point pEnd);

Segment Segment_CreateFromCoords(double x1, double y1, double x2, double y2, double x, double y);

double Segment_CheckXIntersection(Segment segmentVoid, double y);

Segment *Segment_Cut(Segment segment, Segment *vector, double xInter, double xSource, double ySource);

Point Segment_GetPStart(Segment segmentVoid);

Point Segment_GetPEnd(Segment segmentVoid);

double Segment_GetXBiombo(Segment segmentVoid);

double Segment_GetYBiombo(Segment segmentVoid);

double Segment_GetDistance(Segment segmentVoid);

void Segment_SetPStart(Segment segmentVoid, Point pStart);

void Segment_SetPEnd(Segment segmentVoid, Point pEnd);

void Segment_SetXBiombo(Segment segmentVoid, double xBiombo);

void Segment_SetYBiombo(Segment segmentVoid, double yBiombo);

void Segment_SetDistance(Segment segmentVoid, double distance);

void Segment_Destroy(Segment segmentVoid);

#endif
