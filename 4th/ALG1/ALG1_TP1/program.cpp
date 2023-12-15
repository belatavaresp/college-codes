#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

// structure to store coordinates and if the point has been visited
typedef struct Ponto
{
    double x, y;
    bool visited;
    Ponto() : visited(false) {}
} Ponto;

// structure to store information about a point's neighbors
typedef struct Neighbors
{
    int value;
    bool visited;
    double angle;
    Neighbors() : visited(false) {}
} Neighbors;

// function used to calculate polar angle of each point compared to its "father"
double InclinacaoRelativa(Ponto p, Ponto q)
{
    return atan2(q.y - p.y, q.x - p.x);
}

// global variable to keep track of each face
int faceCount = 0;
// graph structure
vector<vector<Neighbors> > graph;
// faces vector
vector<vector<int> > faces;

// parameter function to the std::sort
bool compare(Neighbors &a, Neighbors &b)
{
    return (a.angle < b.angle);
}

// linear search to find next neighbor after father
int get_next(int father, int curr)
{
    size_t i;
    for (size_t n = 0; n < graph[curr].size(); n++)
    {
        if (graph[curr][n].value == father)
        {
            // circular pattern
            if (n == graph[curr].size() - 1)
            {
                i = 0;
            }
            else
            {
                i = n + 1;
            }
        }
    }

    if (i == graph[curr].size())
    {
        i = 0;
    }

    return i;
}

// recursive DFS function to find faces at a given point of graph
void DFS(int father, int curr, vector<Ponto> &points)
{
    int next, ax; // auxiliary variables for "walking" by neighbors

    faces[faceCount].push_back(father);
    graph[father][curr].visited = true;
    ax = graph[father][curr].value;
    next = get_next(father, ax);
    father = ax;
    curr = next;

    // check if we've visited current edge
    if (!graph[father][curr].visited)
    {
        DFS(father, curr, points);
    }
}

int main()
{
    int vertex, edge;
    cin >> vertex >> edge;

    // resizing so we can access positions directly
    vector<Ponto> points(vertex);
    graph.resize(vertex, vector<Neighbors>());
    faces.resize(edge + 2 - vertex); // Euler's formula for faces

    // reading data and building graph structure
    for (int i = 0; i < vertex; i++)
    {
        double x, y;
        int degree;

        cin >> x >> y >> degree;
        graph[i].resize(degree);
        points[i].x = x;
        points[i].y = y;

        for (int k = 0; k < degree; k++)
        {
            int neighbor;
            cin >> neighbor;
            graph[i][k].value = neighbor - 1;
        }
    }

    // sorting the adjacency lists by polar angle
    for (int i = 0; i < vertex; i++)
    {
        for (size_t j = 0; j < graph[i].size(); j++)
        {
            graph[i][j].angle = InclinacaoRelativa(points[i], points[graph[i][j].value]);
        }
        sort(graph[i].begin(), graph[i].end(), compare);
    }

    // calling the RecursiveDFS for non-visited points of graph only
    for (int i = 0; i < vertex; i++)
    {
        if (!points[i].visited && graph[i].size() != 1)
        {
            for (size_t j = 0; j < graph[i].size(); j++)
            {
                if (!graph[i][j].visited)
                {
                    DFS(i, j, points);
                    faces[faceCount].push_back(i); // adding fist point at end of face
                    faceCount++;
                }
            }
            points[i].visited = true;
        }
    }

    // printing results
    cout << faceCount << endl;
    for (int f = 0; f < faceCount; f++)
    {
        cout << faces[f].size() << " ";
        for (size_t k = 0; k < faces[f].size(); k++)
        {
            cout << faces[f][k] + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
