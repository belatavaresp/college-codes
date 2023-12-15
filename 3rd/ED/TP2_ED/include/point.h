#ifndef POINT_H
#define POINT_H

#include "vector.h"
#include <cmath>

// ---------------------------------------------
// THIS HEADER HAS ALL THE UTILITY FUNCTIONS
// THAT PROCESS POINT'S DATA
// ---------------------------------------------

// structure of a cartesian point in R^2
typedef struct Point
{
    int x;
    int y;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Point()
    {
        this->x = 0;
        this->y = 0;
    }
} point;

// A global reference point
point p0;

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
inline int orientation(point p, point q, point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;             // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// A utility function to find next to top in a vector
inline point nextToTop(Vector<point> *S)
{
    point p = S->top();
    S->pop();
    point res = S->top();
    S->push(p);
    return res;
}

// A utility function to swap two points
inline void swap(point &p1, point &p2)
{
    point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
inline int distSq(point p1, point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

// A function used to sort an array of
// points with respect to the reference point
inline int compare(const void *vp1, const void *vp2)
{
    point *p1 = (point *)vp1;
    point *p2 = (point *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0) // collinear
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

inline int comparePolar(point pi, point pj, point pk)
{
    // if two points lie on opposite side
    // of x-axis, then simply return above
    // point as it has smaller polar angle
    if (pk.y - pi.y >= 0 && pj.y - pi.y < 0)
    {
        return 1;
    }
    if (pk.y - pi.y < 0 && pj.y - pi.y >= 0)
    {
        return -1;
    }

    // Check if both vectors are collinear
    if (orientation(pi, pj, pk) == 0)
    {

        // Check if the vector lies on the y-axis
        if (pk.x - pi.x == 0 && pj.x - pi.x == 0)
        {
            // If vector lie on the y-axis
            // Then return -1, If vector pk-pi
            // has smaller magnitude
            // In comparison to pj-pi
            // Since vector with smaller
            // Magnitude has its end-point
            // Closer to the origin point p0
            if (abs(pk.y - pi.y) > abs(pj.y - pi.y))
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

        // If vectors do not lie on the y-axis,
        // Then, either vector lie on the
        // x-axis or lie in the Same line.

        // Check if vectors lie on x-axis
        // and are on opposite side of y-axis
        // In such a case, return the vector
        // which lies on the positive x-axis
        // since it is in the first quadrant
        // and closer to origin
        if (pk.x - pi.x > 0 && pj.x - pi.x < 0)
        {
            return 1;
        }
        else if (pk.x - pi.x < 0 && pj.x - pi.x > 0)
        {
            return -1;
        }
        // In other cases, return the point
        // closer to the reference point
        else if (abs(pk.x - pi.x) > abs(pj.x - pi.x))
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    // If vectors lie on same side
    // of y-axis and are not collinear,
    // Then compare them using Cross product
    if (orientation(pi, pj, pk) == 1)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// A utility function to calculate the polar angle
// of a given point and the global p0
inline double calculatePolarAngle(point point)
{
    double deltaY = point.y - p0.y;
    double deltaX = point.x - p0.x;
    return std::atan2(deltaY, deltaX);
}

// A utility function to print point coordinates
// in a vector structure
inline void print(Vector<point> *v)
{
    if (v->getSize() == 0)
        return;
    for (int i = 0; i < v->getSize(); i++)
    {
        std::cout << v->at(i).x << "  ";
        std::cout << v->at(i).y << std::endl;
    }
    std::cout << std::endl;
}

inline void printConvexHullEquations(Vector<point>& convexHull) {
    int n = convexHull.getSize();

    for (int i = 0; i < n; i++) {
        const Point& p1 = convexHull.at(i);
        const Point& p2 = convexHull.at((i + 1) % n); // Wrap around to the first point

        // Calculate the equation of the line in the form "y = mx + c"
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;

        if (dx == 0) {
            // Vertical line, equation is of the form "x = c"
            std::cout << "x = " << p1.x << std::endl;
        } else {
            // Non-vertical line, equation is of the form "y = mx + c"
            double m = static_cast<double>(dy) / dx;
            double c = p1.y - m * p1.x;
            std::cout << "y = " << m << "x + " << c << std::endl;
        }
    }
    std::cout << std::endl;
}

#endif
