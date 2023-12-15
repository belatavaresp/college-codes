#include "sorts.h"
#include "point.h"

// ---------------------------------------------
// THIS HEADER CONTAINS A STANDARD
// IMPLEMENTATION OF A JARVIS' ALGORITHM
// TO FIND THE CONVEX HULL OF GIVEN POINTS
// ---------------------------------------------

// GENERAL LOGIC: --------------------------------------------------------------------------------------
// The algorithm starts with the leftmost point (after sorting the given points)
// and iteratively finds the next point on the convex hull
// in a counterclockwise manner.
// It repeatedly selects the most counterclockwise point relative to
// the current point and adds it to the hull.
// By doing so, it constructs the convex hull by wrapping
// around the outermost points of the given set.

// USING MERGE SORT ------------------------------------------------------------------------------------

Vector<point>& jarvis(Vector<point> &entry, int size)
{
    Vector<point> *hull = new Vector<point>;

    Vector<point> points(size);
    entry.copy(points);
    // There must be at least 3 points
    if (size < 3)
        return entry;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < size; i++)
            if (points.at(i).x < points.at(l).x)
                l = i;
                
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again. O(h) --> size of hull
    int p = l, q;
    do
    {
        // Add current point to result
        hull->push(points.at(p));

        // Search for a point 'q' such that orientation(p, q,
        // x) is counterclockwise for all points 'x'.
        q = (p + 1) % size;
        for (int i = 0; i < size; i++)
        {
            if (orientation(points.at(p), points.at(i), points.at(q)) == 2)
                q = i;
        }

        p = q;

    } while (p != l); // While we don't come to first point

    return *hull;
}