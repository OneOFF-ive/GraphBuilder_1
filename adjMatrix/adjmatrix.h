#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "myGraphicsView/mygraphicsview.h"
#include "adjTable/adjtable.h"


#define INF 101

struct Vex {
    int no;
    int pre;

    Vex(int n, int p) : no(n), pre(p) {};
    Vex() = default;
};

struct DijkVex : public Vex {
//    int no;
//    int pre;
    int dist;
    int dijkstraStart;

    DijkVex(int n, int p, int d, int s) : Vex(n, p), dist(d), dijkstraStart(s) {};
    DijkVex() = default;
};

struct Edge {
    //起点
    int u;
    //终点
    int v;
    //权值
    int w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {};
    Edge() = default;
};

class AdjMatrix
{
public:
    AdjMatrix(const MyGraphicsView *view);
    ~AdjMatrix();

    void displayMatrix() const;

    QQueue<DijkVex> Dijkstra(int v) const;
    QQueue<DijkVex> DijkstraPath(int v, int end) const;
    QQueue<DijkVex> FloydPath(int v, int end) const;

    QQueue<Vex> Kruskal() const;
    QQueue<Vex> Prim(int v) const;

private:
    int size;
    int **matrix;
    int lineNum;
};

#endif // ADJMATRIX_H
