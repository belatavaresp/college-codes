#include "sorts.h"
#include "point.h"

// ---------------------------------------------
// THIS HEADER CONTAINS A STANDARD
// IMPLEMENTATION OF A GRAHAM'S SCAN ALGORITHM
// TO FIND THE CONVEX HULL OF GIVEN POINTS
// ---------------------------------------------

// GENERAL LOGIC: --------------------------------------------------------------------------------------
// The Graham's scan algorithm starts by finding the bottommost
// point (sorting by y) and sorting the remaining points based
// on their polar angles. It removes duplicate points and handles
// cases where points have the same angle with respect to p0.
// Then, it iteratively processes the remaining points,
// removing points that create non-left turns, and adding
// the points to the convex hull vector S.

// USING MERGE SORT: --------------------------------------------------------------------------------------

Vector<point> &grahamMerge(Vector<point> &entry, int size)
{
   Vector<point> *S = new Vector<point>;

   Vector<point> points(size);
   entry.copy(points);
   // Find the bottommost point
   int ymin = points.at(0).y;
   mergeSortY(points.getData(), size);
   ymin = points.at(0).y;

   p0 = points.at(0);
   mergePolar(points, 1, size - 1, p0);

   int newSize = 1; // Initialize size of modified array
   for (int i = 1; i < size; i++)
   {
      while (i < size - 1 && orientation(p0, points.at(i),
                                         points.at(i + 1)) == 0)
         i++;

      points.at(newSize) = points.at(i);
      newSize++; // Update size of modified array
   }

   // If modified array of points has less than 3 points,
   // convex hull is not possible
   if (newSize < 3)
      return entry;

   S->push(points.at(0));
   S->push(points.at(1));
   S->push(points.at(2));

   // Process remaining size-3 points
   for (int i = 3; i < newSize; i++)
   {
      while (S->getSize() > 1 && orientation(nextToTop(S), S->top(), points.at(i)) != 2)
         S->pop();
      S->push(points.at(i));
   }

   return *S;
}

// USING INSERTION SORT: --------------------------------------------------------------------------------------

Vector<point> &grahamInsertion(Vector<point> &entry, int size)
{
   Vector<point> *S = new Vector<point>;

   Vector<point> points(size);
   entry.copy(points);
   // Find the bottommost point
   int ymin = points.at(0).y;
   insertionSortY(points.getData(), size);
   ymin = points.at(0).y;

   p0 = points.at(0);
   insertionSortPolar(&points.at(1), size - 1);

   int newSize = 1; // Initialize size of modified array
   for (int i = 1; i < size; i++)
   {
      while (i < size - 1 && orientation(p0, points.at(i),
                                         points.at(i + 1)) == 0)
         i++;

      points.at(newSize) = points.at(i);
      newSize++; // Update size of modified array
   }

   // If modified array of points has less than 3 points,
   // convex hull is not possible
   if (newSize < 3)
      return entry;

   S->push(points.at(0));
   S->push(points.at(1));
   S->push(points.at(2));

   // Process remaining size-3 points
   for (int i = 3; i < newSize; i++)
   {
      while (S->getSize() > 1 && orientation(nextToTop(S), S->top(), points.at(i)) != 2)
         S->pop();
      S->push(points.at(i));
   }

   return *S;
}

// USING RADIX SORT: --------------------------------------------------------------------------------------

Vector<point> &grahamRadix(Vector<point> &entry, int size)
{
   Vector<point> *S = new Vector<point>;

   Vector<point> vec(size);
   entry.copy(vec);

   point *points = vec.getData();
   // Find the bottommost point
   int ymin = points[0].y;
   radixSortY(points, size);
   ymin = points[0].y;

   point p0 = points[0];
   radixSortPolar(points + 1, size - 1);

   int newSize = 1; // Initialize size of the modified array
   for (int i = 1; i < size; i++)
   {
      while (i < size - 1 && orientation(p0, points[i], points[i + 1]) == 0)
         i++;

      points[newSize] = points[i];
      newSize++; // Update size of modified array
   }

   // If the modified array of points has less than 3 points,
   // the convex hull is not possible
   if (newSize < 3)
      return entry;

   S->push(points[0]);
   S->push(points[1]);
   S->push(points[2]);

   // Process the remaining size-3 points
   for (int i = 3; i < newSize; i++)
   {
      while (S->getSize() > 1 && orientation(nextToTop(S), S->top(), points[i]) != 2)
         S->pop();
      S->push(points[i]);
   }

   return *S;
}
//--------------------------------------------------------------------------------------------------------