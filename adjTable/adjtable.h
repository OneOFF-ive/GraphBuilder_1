#ifndef ADJTABLE_H
#define ADJTABLE_H

#include "myGraphicsView/mygraphicsview.h"


struct LineNode {
    //邻接点的编号
    int adjVexNo;
    int weight;
    LineNode *nextLine;
};

struct VexNode {
    int no;
    int pre;
    QString tag;
    LineNode *firstLine;
};


class AdjTable
{
public:
    AdjTable(const MyGraphicsView *graphicsView);
    ~AdjTable();
    void displayTable() const;

    const VexNode* Table();

    QQueue<VexNode> BFS_UnConnect(int v);
    QQueue<VexNode> DFS_UnConnect(int v);
private:
    bool isDirected;
    int size;
    VexNode *table;
    int *visited;

    void BFS_Connect(int v, QQueue<VexNode> &visitedQueue);
    void DFS_Connect(int v, int pre, QQueue<VexNode> &visitedQueue);
};

#endif // ADJTABLE_H
