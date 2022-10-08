#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsPathItem>
#include <QObject>
#include <vexItem/vexitem.h>
#include <QPainterPath>

class LineItem : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
    Q_PROPERTY(bool isVisited READ IsVisited WRITE setIsVisited)
private:
    //线起点位置的图元
    VexItem *startVex;
    //线终点位置的图元
    VexItem *endVex;
    //线的起点坐标，初始化时可以以一个起始图元做起点，起点坐标即起始图元的坐标
    QPointF startPoint;
    //线的终点坐标，该坐标在创建直线时随鼠标不断变化，在选定终点图元时等于终点图元的坐标
    QPointF endPoint;
    //图元的颜色，用来初始化和重绘图元
    QColor color;
    //线条是否被选择，默认没被选择
    bool isSelected;
    //该边的权值,默认为0
    int weight;
    //该边是否有方向，默认有方向
    bool isDirected;
    //是否在遍历
    bool isVisited;

    QString tag;
    int no;
public:
    static int number;

    LineItem(VexItem *startVex = nullptr, VexItem *endVex = nullptr, bool directed = true, QGraphicsItem *parent = nullptr);

    //设置起点图元和终点图元
    void setStartVex(VexItem *startVex);
    void setEndvex(VexItem *endVex);
    //设置起点和终点
    void setStartPoint(QPointF startPoint);
    void setEndPoint(QPointF endPoint);
    //计算线条路径
    QPainterPath getPath() const;
    //计算线条的形状
    QPainterPath shape() const override;
    //计算线条的框架
    QRectF boundingRect() const override;
    //画线条
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    bool IsSelected() const;
    //设置被选择状态
    void setSelected();
    //设置未被选择状态
    void setUnSelected();

    //设置为没有方向
    void setUnDirected();
    //设置为有方向
    void setDirected();

    //设置是否在遍历
    void setVisited();
    void setUnVisited();

    void setIsVisited(bool is);

    bool IsVisited() const;

    VexItem * getStartVex() const;
    VexItem * getEndVex() const;

    int No() const;
    void setNo(int n);

    QString getTag() const;
    void setWeight(int w);
    int getWeight() const;

    ~LineItem() = default;
};

#endif // LINEITEM_H
