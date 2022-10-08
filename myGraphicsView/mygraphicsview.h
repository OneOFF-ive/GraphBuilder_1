#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QList>
#include <lineItem/lineitem.h>
#include <vexItem/vexitem.h>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

struct VexNode;

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QWidget *parent = nullptr);
private:
    //打包一个scene，在构造函数中完成初始化
    QGraphicsScene *scene;
   //储存视图中的边和点
    QVector<VexItem *> vexs;
    QVector<LineItem *> lines;

    //当前鼠标点击选择的点,也就是可以操作的点,没选择则为空指针
    VexItem *currentSelectVex = nullptr;
    //当前鼠标点击选择的边,也就是可以操作的边,没选择则为空指针
    LineItem *currentSelectLine = nullptr;
    //正在生成的边
    LineItem *creatingLine = nullptr;

    //当前图是否有方向, 默认为有方向
    bool isDirected;

    //串口动画播放容器
    QSequentialAnimationGroup *AnimationGroup;

    //当前是否正在遍历图
    bool isVisiting;

    QVector<VexItem *> visitedVexs;
    QVector<LineItem *> visitedLines;

public:
    //在容器和scene中添加边和点，显示在view中
    void addVex(VexItem *vex);
    void addLine(LineItem *line);

    //在容器和scene中移除边和点
    void delVex(VexItem *vex);
    void delLine(LineItem *line);

    //鼠标右键点击的位置创建一个点或边，左键选择一个点或边
    void mousePressEvent(QMouseEvent *event) override;
    //根据鼠标移动生成边
    void mouseMoveEvent(QMouseEvent *event) override;

    //删除选中的点或线
    void removeSelectItem();
    //设置是否有向
    void setDirected();
    void setUnDirected();

    int linesNumber() const;
    int vexNumber() const;

    bool IsDirected() const;

    template<typename T> static void deleteVectorItem(QVector<T *> &vector, T *delItem);

    const QVector<VexItem *> &Vexs() const;
    const QVector<LineItem *> &Lines() const;

    void BFS();
    void DFS();
    void Dijkstra();
    void Kruskal();
    void Prim();
    void Floyd();

    //清空试图
    void clearView();

    //播放遍历动画
    template<typename T>
    void playAnimation(QQueue<T> visitedQueue);

    //生成并输出邻接表
    void buildAdjtable();
    //生成并输出邻接矩阵
    void buildAdjMatrix();
signals:
    void mouseClicked();
    void buildLOG(QString log);
};


template<typename T> void MyGraphicsView::deleteVectorItem(QVector<T *> &vector, T *delItem)
{
    if(vector.empty()) return;
    for (auto iter = vector.begin(); iter != vector.end(); ) {
        if (*iter == delItem) {
            vector.erase(iter);
            break;
        }
        else {
            iter++;
        }
    }
}

#endif // MYGRAPHICSVIEW_H
