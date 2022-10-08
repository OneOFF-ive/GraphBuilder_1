#include "lineitem.h"
#include <math.h>
#include <QRandomGenerator>

int LineItem::number = 0;

LineItem::LineItem(VexItem *startVex, VexItem *endVex, bool directed, QGraphicsItem *parent) : QGraphicsPathItem(parent) ,startVex(startVex), endVex(endVex)
{
    startPoint = QPointF(0, 0);
    endPoint = QPointF(0, 0);
    if (startVex != nullptr) {
        startPoint = QPointF(startVex->pos().x(), startVex->pos().y() - 10);
        endPoint = QPointF(startVex->pos().x(), startVex->pos().y() - 10);
    }
    if (endVex != nullptr) {
        endPoint = QPointF(endVex->pos().x(), endVex->pos().y() - 10);
    }

    //设置线条可选
    setFlag(QGraphicsItem::ItemIsSelectable);
    //设置线条在所有图元下层
    setZValue(-1);
    //设置画笔颜色
    color = QColor(58, 143, 192);

    //创建图元时，默认不是被选择状态
    isSelected = false;

    //默认权值为1
    weight = QRandomGenerator::global()->bounded(1, 20);
    //默认有方向
    isDirected = directed;

    LineItem::number++;
    no = number - 1;
    tag = QString::number(no);
}

void LineItem::setStartVex(VexItem *startVex)
{
    this->startVex = startVex;
    startPoint = QPointF(startVex->pos().x(), startVex->pos().y() - 10);
    update();
}

void LineItem::setEndvex(VexItem *endVex)
{
    this->endVex = endVex;
    endPoint = QPointF(endVex->pos().x(), endVex->pos().y());
    update();
}

void LineItem::setStartPoint(QPointF startPoint)
{
    this->startPoint = startPoint;
    update();
}

void LineItem::setEndPoint(QPointF endPoint)
{
    this->endPoint = endPoint;
    update();
}

QPainterPath LineItem::getPath() const
{
    QPainterPath _path(startPoint);
    _path.lineTo(endPoint);
    return _path;
}

QPainterPath LineItem::shape() const
{
    return getPath();
}

QRectF LineItem::boundingRect() const
{
    return getPath().boundingRect();
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (startVex != nullptr) {
        startPoint = QPointF(startVex->pos().x(), startVex->pos().y() - 10);
    }
    if (endVex != nullptr) {
        if (endVex != startVex) {
            endPoint = QPointF(endVex->pos().x(), endVex->pos().y() - 10);
        }
        //当起点和终点一样时
        else {
            endPoint = QPointF(endVex->pos().x() - 100, endVex->pos().y() - 10);
        }
    }

    setPath(getPath());
    QPen pen(color);
    pen.setWidth(5);
    painter->setRenderHint(QPainter::Antialiasing);
    //如果此时还没有选中终点图元，则画虚线
    if (endVex == nullptr) {
        pen.setStyle(Qt::DashDotDotLine);
    }
    else {
        pen.setStyle(Qt::SolidLine);
    }
    //画线条
    painter->setPen(pen);
    painter->drawPath(path());
    //画权值信息
    QFont font;
    font.setPointSize(15);
    painter->setFont(font);
    QPointF textPoint(boundingRect().center().x(), boundingRect().center().y() - 10);
    painter->drawText(textPoint, QString::number(weight));


    //如果有方向，画箭头
    if (isDirected) {

        //确定箭头顶点的位置，用三角函数关系确定
        QPointF topPoint;           //箭头顶点
        QPointF fPoint;             //箭头对称轴上的一个点，和顶点一起构成法线，用于确认其他两个点的位置坐标
        if(endVex == startVex) {
            topPoint = QPointF(endVex->pos().x() - 20, endVex->pos().y() - 10);
            fPoint = QPointF(topPoint.x() - 10, topPoint.y());
        }
        else {
            float _angle = atan(abs(endPoint.x() - startPoint.x()) / abs(endPoint.y() - startPoint.y()));
            float m = 20 * sin(_angle);
            float n = 20 * cos(_angle);
            float new_x, new_y;
            if (endPoint.x() > startPoint.x()) {
                new_x = endPoint.x() - m;
            }
            else {
                new_x = endPoint.x() + m;
            }
            if (endPoint.y() > startPoint.y()) {
                new_y = endPoint.y() - n;
            }
            else {
                new_y = endPoint.y() + n;
            }
            topPoint = QPointF(new_x, new_y);
            fPoint = startPoint;
        }
        //确定箭头另外两个顶点的位置
        QLineF line(fPoint, topPoint);
        double angle = std::atan2(-line.dy(), line.dx());
        qreal arrowSize = 15;
        QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
        QPolygonF arrowHead;
        arrowHead  << line.p2() << arrowP2 << arrowP1;

        painter->drawLine(topPoint, arrowP1);
        painter->drawLine(topPoint, arrowP2);
    }
}

bool LineItem::IsSelected() const
{
    return isSelected;
}

void LineItem::setSelected()
{
    color = QColor(208, 90, 110);
    update();
    isSelected = true;
}

void LineItem::setUnSelected()
{
    color = QColor(58, 143, 192);
    update();
    isSelected = false;
}

void LineItem::setUnDirected()
{
    isDirected = false;
    update();
}

void LineItem::setDirected()
{
    isDirected = true;
    update();
}

bool LineItem::IsVisited() const
{
    return isVisited;
}

VexItem * LineItem::getStartVex() const
{
    return startVex;
}

VexItem *LineItem::getEndVex() const
{
    return endVex;
}

int LineItem::No() const
{
    return no;
}

void LineItem::setNo(int n)
{
    no = n;
}

QString LineItem::getTag() const
{
    return tag;
}

void LineItem::setWeight(int w)
{
    weight = w;
}

int LineItem::getWeight() const
{
    return weight;
}

void LineItem::setVisited()
{
    color = QColor(43, 255, 131);
    update();
    isVisited = true;
}

void LineItem::setUnVisited()
{
    if (isSelected) {
        color = QColor(208, 90, 110);
    }
    else {
        color = QColor(58, 143, 192);
    }
    update();
    isVisited = false;
}

void LineItem::setIsVisited(bool is)
{
    isVisited = is;
    color = QColor(43, 255, 131);
    update();
}
