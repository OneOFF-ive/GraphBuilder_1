#include "vexitem.h"
#include <QPainter>
#include "lineItem/lineitem.h"

int VexItem::number = 0;

VexItem::VexItem(QPointF point, QGraphicsItem *parent) : QGraphicsItem(parent) {
    //设置可选和可移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    //设置创建该点的位置，通常是鼠标的点击位置
    setPos(point);
    //每次创建一个点对象，number++, 点的编号no和标签tag等于number；
    VexItem::number++;
    no = number - 1;
    tag = QString::number(no);
    //设置画笔颜色
    color = QColor(58, 143, 192);
    //创建图元时，默认不是被选择状态和被遍历状态
    isSelected = false;
    isVisited = false;

    //迪杰斯特拉遍历，默认全是未遍历
    pre = -1;
    dist = -1;
    start = -1;
}

int VexItem::type() const
{
    return UserType + 1;
}

QRectF VexItem::boundingRect() const
{
    return QRectF(-20, -30, 40 ,60);
}

void VexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //设置抗锯齿
    painter->setRenderHint(QPainter::Antialiasing);
    //设置圆无边框
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-20, -30, 40, 40);
    //写tag
    painter->setPen(QPen(Qt::black));
    painter->drawText(-3, 25, tag);
}

int VexItem::No() const
{
    return no;
}

void VexItem::setNo(int n)
{
    no = n;
}

bool VexItem::IsSelected() const
{
    return isSelected;
}

QString VexItem::getTag() const
{
    return tag;
}

void VexItem::setTag(QString t)
{
    tag = t;
    update();
}

void VexItem::setSelected()
{
    color = QColor(208, 90, 110);
    update();
    isSelected = true;
}

void VexItem::setUnSelected()
{
    color = QColor(58, 143, 192);
    update();
    isSelected = false;
}

void VexItem::addLine(LineItem *line)
{
    lines.push_back(line);
}

void VexItem::setVisited()
{
    color = QColor(43, 255, 131);
    update();
    isVisited = true;
}

void VexItem::setUnVisited()
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

void VexItem::setIsVisited(bool is)
{
    isVisited = is;
    color = QColor(43, 255, 131);
    update();
}

bool VexItem::IsVisited() const
{
    return isVisited;
}

void VexItem::setPre(int p)
{
    pre = p;
}

int VexItem::getPre() const
{
    return pre;
}

void VexItem::setDist(int d)
{
    dist = d;
}

int VexItem::getDist() const
{
    return dist;
}

void VexItem::setStart(int s)
{
    start = s;
}

int VexItem::getStart() const
{
    return start;
}

QVector<LineItem *> &VexItem::Lines()
{
    return lines;
}

