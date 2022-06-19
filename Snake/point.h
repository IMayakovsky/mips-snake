#ifndef POINT_H
#define POINT_H

typedef struct Point
{
    int x;
    int y;
} Point;

/**
 * Returns Point with x and y coordinates
 */
Point GetPoint(int x, int y);

#endif //POINT_H