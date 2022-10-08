#include "adjmatrix.h"
#include <iostream>
#include <QQueue>
#include <QStack>
#include <QtDebug>


AdjMatrix::AdjMatrix(const MyGraphicsView *view)
{
    size = view->vexNumber();
    lineNum = view->linesNumber();

    matrix = new int *[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = INF;
            }
        }
    }

    for (auto &line: view->Lines()) {
        matrix[line->getStartVex()->No()][line->getEndVex()->No()] = line->getWeight();
        //无向图，矩阵对称
        if (!view->IsDirected()) {
            matrix[line->getEndVex()->No()][line->getStartVex()->No()] = line->getWeight();
        }
    }
}

AdjMatrix::~AdjMatrix()
{
    for (int i = 0; i < size; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

void AdjMatrix::displayMatrix() const
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] != INF) {
                std::cout<<matrix[i][j]<<"  "<<std::ends;
            }
            else {
                std::cout<<"INF"<<"  "<<std::ends;
            }
        }
        std::cout<<std::endl;
    }
}

QQueue<DijkVex> AdjMatrix::Dijkstra(int v) const
{
    QQueue<DijkVex> visitedQueue;

    /*
     *dist[i]表示v到i的最短距离
     *但在最开始dist[i]代表v直接到i的距离，没有中间点，所以还不是最终结果
     *每遍历一个点u，即代表v到i之间多了一个中间点u，需要修改所有和u有关的点的dist[j]，遍历完所有点后dist[i]就可以代表v到i点最小距离
     *path[i]表示v到i的最短路径上i的前驱点，可以通过该数组反推出一条v到i的路径
     *S表示已遍历的点，U表示未遍历的点
     *每次从U中挑选权值最小的边，假设该边的终点是u，将u置入S中，代表其已被遍历，然后修改有关的dist[i]
     *判断dist[u]+weight(u,j)和dist[j]的大小，另dist[j] = 两者的最小值
     *循环遍历所有的点
     */
    int dist[size], path[size];
    //如果S[i] = 1，则表明i在S中，否则在U中
    int S[size];
    //S中权值最小的边的权值
    int minDist;

    //初始化path和S，如果v到i有边，则path[i]=v，否则=-1
    for (int i = 0; i < size; i++) {
        dist[i] = matrix[v][i];
        S[i] = 0;
        if (matrix[v][i] != INF) {
            path[i] = v;
        }
        else {
            path[i] = -1;
        }
    }
    //源点v已遍历，前驱为自己
    S[v] = 1;
    path[v] = v;

    //将遍历过的点存入容器中，用于动画演示
    visitedQueue.enqueue(DijkVex(v, path[v], dist[v], v));

    //开始遍历点u，除了点v，一共需要遍历n-1个点
    int u = v;
    for (int i = 0; i < size - 1; i++) {
        //在U中寻找权值最小的边
        minDist = INF;
        for (int j = 0; j < size; j++) {
            if (S[j] == 0 and dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }
        //权值最小的边的终点是u，将u放入S中
        S[u] = 1;

        //修改U中所有和点u有关的点的最短距离dist[i]
        for (int j = 0; j < size; j++) {
            if (S[j] == 0) {
                if (matrix[u][j] < INF and dist[u] + matrix[u][j] < dist[j]) {
                    dist[j] = dist[u] + matrix[u][j];
                    path[j] = u;
                }
            }
        }
        //u点被遍历，将其放入容器中储存
        visitedQueue.enqueue(DijkVex(u, path[u], dist[u], v));
    }
    return visitedQueue;
}

QQueue<DijkVex> AdjMatrix::DijkstraPath(int v, int end) const
{
    QQueue<DijkVex> visitedQueue = Dijkstra(v);

    QQueue<DijkVex> aniQueue;
    QStack<DijkVex> aniStack;
    int endIndex = -1;

    //判断是否能够遍历到终点
    for (int i = 0; i < visitedQueue.size(); i++) {
        if (visitedQueue[i].no == end) {
            endIndex = i;
            break;
        }
    }
    //遍历到终点
    if (endIndex != -1) {
        int i = endIndex;
        while (visitedQueue[i].pre != visitedQueue[i].no) {
            aniStack.push_back(visitedQueue[i]);
            for (int j = 0; j < visitedQueue.size(); j++) {
                if (visitedQueue[j].no == visitedQueue[i].pre) {
                    i = j;
                    break;
                }
            }
        }
        //起点
        aniStack.push_back(visitedQueue[0]);
    }

    while (!aniStack.empty()) {
        DijkVex vex = aniStack.pop();
        aniQueue.enqueue(vex);
    }

    return aniQueue;
}

QQueue<DijkVex> AdjMatrix::FloydPath(int start, int end) const
{
    /*
     * Ak[i][j]表示i到j的最短距离，可以路过标号小于等于k的点
     * 遍历n次，就可以得到An[i][j]，表示i到j的最短距离，可以经过任何点
     * 每次遍历一个点k,需要比较Ak-1[i][j]和Ak-1[i][k]+Ak-1[k][j]的大小
     * 并使Ak[i][j]取较小值
     * path[i][j]表示在第i到j的最短路径中j的前驱点
     * 如果Ak-1[i][k]+Ak-1[k][j]小于Ak-1[i][j]，则path[i][j]=path[k][j]
     */
    int A[size][size], path[size][size];
    //初始化A[i][j]和path[i][j]
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = matrix[i][j];
            if (i != j and matrix[i][j] < INF) {
                path[i][j] = i;
            }
            else {
                path[i][j] = -1;
            }
        }
    }
    //修改N次A和path
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    //利用path追溯一条路径
    QQueue<DijkVex> aniQueue;
    QStack<DijkVex> aniStack;

    if (A[start][end] != INF and start != end) {
        int pre = path[start][end];
        //终点
        DijkVex vex(end, pre, A[start][end], start);
        aniStack.push_back(vex);

        //中间点
        int k = pre;
        while (k != -1 and k != start) {
            pre = path[start][k];
            vex = DijkVex(k, pre, A[start][k], start);
            k = pre;
            aniStack.push(vex);
        }

        //起点
        aniStack.push_back(DijkVex(start, start, 0, start));
    }



    //栈转化为队列，用于动画演示
    while (!aniStack.empty()) {
        DijkVex vex = aniStack.pop();
        aniQueue.enqueue(vex);
    }

    return aniQueue;
}

//直接插入排序
void insertSort(Edge *edges, int totalE);

//无向图连通图
QQueue<Vex> AdjMatrix::Kruskal() const
{
    //储存已生成的边
    QQueue<Edge> buildLine;

    int vset[size];
    for (int i = 0; i < size; i++) {
        vset[i] = i;
    }
    /*
     * vest是一个辅助数组，他储存图中每一个顶点的连通分量，即vest[i]表示顶点i的连通分量；
     * 初始时每个顶点的连通分量等于顶点的编号，即vest[i]=i；
     * 当选中一条边（i，j）时，如果vest[i] = vest[j]，则表示顶点i和顶点j在一条通路上，此时再加入边（i，j）则会生成回路，所以（i，j）需要被抛弃；
     * 如果vest[i]!=vest[j]，则将边（i，j）加入通路，并将这两个顶点所在的连通路上所有顶点的连通分量改成相同数值
     */
    Edge E[lineNum];        //存放图中所有的边
    int k = 0;              //E数组的下标
    //遍历matrix，将每条边都存进E数组
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            if (matrix[i][j] != 0 and matrix[i][j] != INF) {
                E[k].u = i;
                E[k].v = j;
                E[k].w = matrix[i][j];
                k++;
            }
        }
    }
    insertSort(E, lineNum);

    k = 1;                  //表示目前在生成第几条边
    int j = 0;              //E的下标
    //最小生成树的边数小于等于n-1
    while (k < size) {
        //一条边的两个顶点
        int u1 = E[j].u;
        int v1 = E[j].v;
        //两个顶点的连通分量
        int sn1 = vset[u1];
        int sn2 = vset[v1];

        //两个顶点的连通分量不同，可以生成一条边
        if (sn1 != sn2) {
            buildLine.enqueue(E[j]);                //将这条边放入容器中
            k++;
            //将顶点v所在的连通路上的所有顶点的连通分量改为顶点u的连通分量
            for (int i = 0; i < size; i++) {
                if (vset[i] == sn2) {
                    vset[i] = sn1;
                }
            }
        }
        j++;                //扫描下一条边
    }

    QQueue<Vex> visitedVex;             //将遍历边转变为遍历点，方便动画播放
    for (auto &edge: buildLine) {
        Vex v1(edge.u, edge.u);
        Vex v2(edge.v, edge.u);
        visitedVex.enqueue(v1);
        visitedVex.enqueue(v2);
    }
    return visitedVex;
}

//无向连通图
QQueue<Vex> AdjMatrix::Prim(int v) const
{
    //储存已生成的边
    QQueue<Edge> buildLine;

    /*
     * S表示已遍历的点， U表示未遍历的点
     * closest[i] = k表示i是U中的一个点，k是S中的一个点，（k, i）是i和S中的点所有边中权值最小的边
     * lowcost[i] = w表示(k, i)这条边的权值为w
     * 当一个点属于S时，lowcost[i] = 0, 0 < lowcost[i] < INF表示i属于U
     * 初始时，U中只有v一个点，（v, i）就是任意点i到S权值最小的边，置lowcost[i] = matrix[v][i], closest[i] = v
     * 此时lowcost[v] = 0，表示v在S中
     * 然后扫描U，找出lowcost最小的边，假设lowcost[k]最小，表明(closest[k], k)是最小边，将该边存起来，方便动画演示
     * 将lowcost[k]置为0，表示k进入S
     * 然后对U中所有和点k有关系的边做调整，修改侯选边
     * 假设j时U中的一个点，且j和k之间有一条边，比较lowcost[j]和matrix[k][j]的大小，时lowcost[j]去较小值
     * 循环遍历，知道U为空
     */
    int lowcost[size];
    int min;                    //记录最短侯选边的权值
    int closest[size];

    //初始化
    for (int i = 0; i < size; i++) {
        lowcost[i] = matrix[v][i];
        closest[i] = v;
    }


    int k = v;                  //k是最短侯选边在U中的顶点
    for (int i = 0; i < size; i++) {
        min = INF;
        //在U中寻找最短侯选边
        for (int j = 0; j < size; j++) {
            if (lowcost[j] != 0 and lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
        }
        //将最短侯选边存入容器
        buildLine.enqueue(Edge(closest[k], k, lowcost[k]));
        //将k置入S
        lowcost[k] = 0;
        //调整所有和k有关的侯选边
        for (int j = 0; j < size; j++) {
            if (lowcost[j] != 0 and matrix[k][j] < lowcost[j]) {
                lowcost[j] = matrix[k][j];
                closest[j] = k;
            }
        }
    }

    QQueue<Vex> visitedVex;             //将遍历边转变为遍历点，方便动画播放
    for (auto &edge: buildLine) {
        Vex v1(edge.u, edge.u);
        Vex v2(edge.v, edge.u);
        visitedVex.enqueue(v1);
        visitedVex.enqueue(v2);
    }
    return visitedVex;
}

void insertSort(Edge *edges, int totalE) {
    Edge tmp{};
    for (int i = 1; i < totalE; ++i) {
        if (edges[i].w < edges[i-1].w) {
            tmp = edges[i];
            int j = i - 1;
            while (edges[j].w > tmp.w and j >= 0) {
                edges[j+1] = edges[j];
                j--;
            }
            edges[j+1] = tmp;
        }
    }
}















