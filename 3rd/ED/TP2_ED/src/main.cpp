#include "vector.h"
#include "graham.h"
#include "jarvis.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "USE: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    fstream file;
    file.open(argv[1]);
    if (file.fail())
    {
        cout << "ERROR OPENING FILE" << endl;
        return 1;
    }

    int x, y;
    bool empty = true;
    point *p;

    Vector<point> *currentVector = new Vector<point>;
    Vector<point> *after = new Vector<point>;

    while (!file.eof())
    {
        while (file.peek() != '.' && file >> x >> y)
        {
            empty = false;
            p = new point(x, y);
            currentVector->push(*p);
            file.get();
        }
        file.get();

        if(empty){
        cout << "ERROR EMPTY FILE" << endl;
        return 1;
        }

        clock_t start = clock();
        *after = jarvis(*currentVector, currentVector->getSize());
        clock_t end = clock();
        double time = double(end - start) / CLOCKS_PER_SEC;
        insertionSortY(after->getData(), after->getSize());
        cout << "\nFECHO CONVEXO:\n";
        print(after);
        cout << "JARVIS: ";
        cout << fixed << setprecision(3) << time << " s" << endl << endl;

        cout << "GRAHAM + MERGESORT: ";
        start = clock();
        *after = grahamMerge(*currentVector, currentVector->getSize());
        end = clock();
        time = double(end - start) / CLOCKS_PER_SEC;
        cout << fixed << setprecision(3) << time << " s" << endl << endl;
        insertionSortY(after->getData(), after->getSize());

        cout << "GRAHAM + INSERTIONSORT: ";
        after->clear();
        start = clock();
        *after = grahamInsertion(*currentVector, currentVector->getSize());
        end = clock();
        time = double(end - start) / CLOCKS_PER_SEC;
        cout << setprecision(3) << time << " s" << endl << endl;

        cout << "GRAHAM + RADIXSORT: ";
        after->clear();
        start = clock();
        *after = grahamRadix(*currentVector, currentVector->getSize());
        end = clock();
        time = double(end - start) / CLOCKS_PER_SEC;
        cout << setprecision(3) << time << " s" << endl << endl;
        insertionSortY(after->getData(), after->getSize());

        cout << "EQUAÇÕES:\n";
        printConvexHullEquations(*after);

        currentVector->~Vector();
        after->~Vector();

        currentVector = new Vector<point>;
        after = new Vector<point>;
    }

    currentVector->~Vector();
    after->~Vector();

    if(empty){
        cout << "ERROR EMPTY FILE" << endl;
        return 1;
    }

    return 0;
}
