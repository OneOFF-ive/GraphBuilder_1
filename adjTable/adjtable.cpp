#include "adjtable.h"
#include <iostream>
#include <QQueue>

AdjTable::AdjTable(const MyGraphicsView *graphicsView)
{
    isDirected = graphicsView->IsDirected();
    size = graphicsView->vexNumber();

    table = new VexNode[size];

    visited = new int[size];

    for (int i = 0; i < size; i++) {
        table[i].firstLine = nullptr;
        table[i].pre = i;
    }

    //遍历该视图所有的点
    for (int i = 0; i < graphicsView->Vexs().size(); i++) {
        table[i].no = graphicsView->Vexs()[i]->No();
        table[i].tag = graphicsView->Vexs()[i]->getTag();
        //遍历所有与该点相连的边
        for (int j = 0; j < graphicsView->Vexs()[i]->Lines().size(); j++) {
            //如果是无向图
            if(!isDirected) {
                LineNode *line = new LineNode;
                line->weight = graphicsView->Vexs()[i]->Lines()[j]->getWeight();
                //头插法
                line->nextLine = table[i].firstLine;
                table[i].firstLine = line;
                //该边从该点出发
                if (graphicsView->Vexs()[i]->Lines()[j]->getStartVex()->No() == table[i].no) {
                    line->adjVexNo = graphicsView->Vexs()[i]->Lines()[j]->getEndVex()->No();
                }
                else {
                    line->adjVexNo = graphicsView->Vexs()[i]->Lines()[j]->getStartVex()->No();
                }

            }
            //有向图
            else {
                //该边从该点出发
                if (graphicsView->Vexs()[i]->Lines()[j]->getStartVex()->No() == table[i].no) {
                    LineNode *line = new LineNode;
                    line->weight = graphicsView->Vexs()[i]->Lines()[j]->getWeight();
                    //头插法
                    line->nextLine = table[i].firstLine;
                    table[i].firstLine = line;
                    line->adjVexNo = graphicsView->Vexs()[i]->Lines()[j]->getEndVex()->No();
                }
            }
        }
    }
}

AdjTable::~AdjTable()
{
    LineNode *pre = nullptr, *p = nullptr;
    for (int i = 0; i < size; i++) {
        pre = table[i].firstLine;
        if (pre != nullptr) {
            p = pre->nextLine;
            while (p != nullptr) {
                delete pre;
                pre = p;
                p = pre->nextLine;
            }
            delete pre;
        }
    }
    delete [] table;
    delete visited;
}

void AdjTable::displayTable() const
{
    LineNode *line;
    for (int i = 0; i < size; i++) {
        line = table[i].firstLine;
        std::cout<<table[i].tag.toStdString()<<": "<<std::ends;
        while (line != nullptr) {
            std::cout<<"->"<<table[line->adjVexNo].tag.toStdString()<<"["<<line->weight<<"]"<<std::ends;
            line = line->nextLine;
        }
        std::cout<<std::endl;
    }
}

const VexNode *AdjTable::Table()
{
    return table;
}

void AdjTable::BFS_Connect(int v, QQueue<VexNode> &visitedQueue)
{
    QQueue<int> tmpQueue;

    int preVexNo = v;

    visited[v] = 1;
    visitedQueue.enqueue(table[v]);
    tmpQueue.enqueue(v);

    LineNode *arcline = nullptr;
    while (!tmpQueue.empty()) {
        preVexNo = tmpQueue.front();
        int visitedVexNo = tmpQueue.dequeue();

        arcline = table[visitedVexNo].firstLine;
        while (arcline != nullptr) {
            if (visited[arcline->adjVexNo] == 0) {
                visited[arcline->adjVexNo] = 1;
                tmpQueue.enqueue(arcline->adjVexNo);

                table[arcline->adjVexNo].pre = preVexNo;
                visitedQueue.enqueue(table[arcline->adjVexNo]);
            }
            arcline = arcline->nextLine;
        }
    }
}

QQueue<VexNode> AdjTable::BFS_UnConnect(int v)
{
    QQueue<VexNode> visitedQueue;

    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }
    BFS_Connect(v, visitedQueue);
    for (int i = 0; i < size; i++) {
        if(visited[i] == 0) {
            BFS_Connect(i, visitedQueue);
        }
    }
    return visitedQueue;
}

void AdjTable::DFS_Connect(int v, int pre, QQueue<VexNode> &visitedQueue)
{
    visited[v] = 1;
    table[v].pre = pre;
    visitedQueue.enqueue(table[v]);

    LineNode *arcline = table[v].firstLine;
    while (arcline != nullptr) {
        if (visited[arcline->adjVexNo] == 0) {
            DFS_Connect(table[arcline->adjVexNo].no, table[v].no, visitedQueue);
        }
        arcline = arcline->nextLine;
    }
}

QQueue<VexNode> AdjTable::DFS_UnConnect(int v)
{
    QQueue<VexNode> visitedQueue;

    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }
    DFS_Connect(v, v, visitedQueue);
    for (int i = 0; i < size; i++) {
        if(visited[i] == 0) {
           DFS_Connect(i, i, visitedQueue);
        }
    }
    return visitedQueue;
}






