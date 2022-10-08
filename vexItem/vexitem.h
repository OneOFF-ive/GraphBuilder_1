#ifndef VEXITEM_H
#define VEXITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>

class LineItem;

class VexItem :public QObject,  public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(bool isVisited READ IsVisited WRITE setIsVisited)
private:
    QString tag;
    int no;
    //图元的颜色，用来初始化和重绘图元
    QColor color;
    //标记图元是否被选择
    bool isSelected;
    //标记是否是被遍历状态
    bool isVisited;
    //储存该点上连接的所有边
    QVector<LineItem *> lines;

    //最短路径遍历后该点的前驱点，-1则表示未遍历到该点
    int pre;
    //最短路径遍历后的最短距离，-1表示未遍历到该点
    int dist;
    //最短路径遍历后的起始点no，-1表示未遍历到该点
    int start;

public:
    static int number;

    VexItem(QPointF point, QGraphicsItem *parent = nullptr);
    virtual int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    int No() const;
    void setNo(int n);

    bool IsSelected() const;

    QString getTag() const;
    //修改tag，并重绘图元
    void setTag(QString t);
    //设置图元为被选择状态，并重绘图元
    void setSelected();
    //设置图元为未被选择状态，并重绘图元
    void setUnSelected();
    //增加一条和该点连接的边
    void addLine(LineItem *line);

    //设置是否在遍历
    void setVisited();
    void setUnVisited();

    void setIsVisited(bool is);

    bool IsVisited() const;

    void setPre(int p);
    int getPre() const;
    void setDist(int d);
    int getDist() const;
    void setStart(int s);
    int getStart() const;

    QVector<LineItem *> & Lines();
};

#endif // VEXITEM_H
