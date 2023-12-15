#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <algorithm>

#define ull unsigned long long
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;

typedef struct Road
{
    int from, to;
    int year;
    int time;
    int cost;

    Road() : year(0), time(0), cost(0) {}
    Road(int f, int t, int y, int tm, int c) : from(f), to(t), year(y), time(tm), cost(c) {}

    void print()
    {
        cout << "From: " << from + 1 << "\tTo: " << to + 1 << "\tYear: " << year << "\tTime: " << time << "\tCost: " << cost << endl;
    }
} Road;

vector<int> setRank; // store the ranks in the disjoint-set.
vector<int> parent; // store the parents in the disjoint-set.
int a = -1;

// Aux function for sorting roads by year
bool compareYear(const Road &a, const Road &b)
{
    return a.year < b.year;
}

// Aux function for sorting roads by cost
bool compareCost(const Road &a, const Road &b)
{
    return a.cost < b.cost;
}

// Aux function to compare min heap elements by time then year
class Compare{
    public:
        bool operator()(pair<int, pair<ull,int> > bellow, pair<int, pair<ull,int> >above){
            if(bellow.second.first > above.second.first){
                return true;
            }else if(bellow.second.first == above.second.first && bellow.second.second > above.second.second)
                return true;
            
            return false;
        }
};

// Adjusted union find implementation for opimizing Kruskal
// Function to initialize the disjoint-set.
void makeSet(int n)
{
    setRank.assign(n, 0); // Initialize all ranks to 0.
    parent.resize(n);
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i; // Each element is set as its own parent.
    }
}

// Function to find the parent of a set (with path compression)
int find(int x)
{
    if (x != parent[x])
    {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

// Function to unite two sets (with union by rank)
bool un(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return false; // Already in the same set.

    // Union by rank
    if (setRank[x] > setRank[y])
    {
        parent[y] = x;
    }
    else
    {
        parent[x] = y;
        if (setRank[x] == setRank[y])
        {
            setRank[y]++;
        }
    }
    return true;
}

// kruskal to return first year when all villages are reachable from royal palace
int KruskalYears(vector<Road> roads, int villages)
{
    sort(roads.begin(), roads.end(), compareYear);
    makeSet(villages); // Initialize the disjoint-set.

    int years = 0;
    int connected = 1;

    for (size_t j = 0; j < roads.size(); j++)
    {
        const Road &road = roads[j];

        if (un(road.from, road.to))
        {
            years = road.year;
            connected++;

            if (connected == villages)
            {
                break;
            }
        }
    }
    return years;
}

// kruskal to return smallest cost to make all kingdom reachable
ull KruskalCost(vector<Road> roads, int villages)
{
    sort(roads.begin(), roads.end(), compareCost);
    makeSet(villages); // Initialize the disjoint-set.

    ull cost = 0;
    int connected = 1;

    for (size_t i = 0; i < roads.size(); i++)
    {
        const Road &road = roads[i];

        if (un(road.from, road.to))
        {
            cost += road.cost;
            connected++;
            if (connected == villages)
            {
                break;
            }
        }
    }
    return cost;
}

// dijkstra addaptation to find the first from which it is possible to reach any village in the kingdom from the royal palace
vector<ull> earliestYear(vector<vector<Road> > graph, int royalPalace)
{
    int villages = graph.size();
    vector<ull> distance(villages, inf);
    vector<bool> mark(villages, false);
    distance[royalPalace] = 0;

    // min heap to (village, (time, year))
    priority_queue<pair<int, pair<ull, int> >, vector<pair<int, pair<ull, int> > >, Compare> pq;
    pq.push(make_pair(royalPalace, make_pair(0, -1)));
    a = -1;

    while (!pq.empty())
    {
        int u = pq.top().first; // village
        int top = pq.top().second.second; 
        pq.pop();
        if(mark[u]){
            continue;
        }
        a = max(a, top); // max year yet
        mark[u] = true;
    
        for (size_t i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i].to;
            int y = graph[u][i].year;
            int w = graph[u][i].time;

            if (distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                pq.push(make_pair(v, make_pair(distance[v], y)));

            }
        }
    }
    return distance;
}

int main() {
    // reading the graph's info
    int villages, roads;
    scanf("%d %d", &villages, &roads);
    vector<vector<Road> > graph(villages);
    vector<Road> allRoads(roads);

    for (int i = 0; i < roads; i++) {
        int from, to, year, time, cost;
        scanf("%d %d %d %d %d", &from, &to, &year, &time, &cost);
        graph[from - 1].push_back(Road(from - 1, to - 1, year, time, cost));
        graph[to - 1].push_back(Road(to - 1, from - 1, year, time, cost));
        allRoads[i] = Road(from - 1, to - 1, year, time, cost);
    }

    // first N output lines
    vector<ull> distancesTime = earliestYear(graph, 0);

    // N+1 output line
    int year1 = a;

    // N+2 output line
    int year = KruskalYears(allRoads, villages);

    // N+3 output line
    ull cost = KruskalCost(allRoads, villages);

    // printing output
    for (int i = 0; i < villages; i++) {
        printf("%lld\n", distancesTime[i]);
    }
    printf("%d\n%d\n%lld\n", year1, year, cost);

    return 0;
}