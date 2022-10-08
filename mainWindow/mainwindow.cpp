#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myGraphicsView/mygraphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //鼠标点击时更新信息
    connect(ui->graphicsView, &MyGraphicsView::mouseClicked, [=](){
        infoUpdate();
    });

    connect(ui->graphicsView, &MyGraphicsView::buildLOG, [=](QString log){
        ui->LogList->addItem(log);
        ui->LogList->setCurrentRow(ui->LogList->count()-1);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::infoUpdate()
{
    ui->vexsNum->setText(QString::number(ui->graphicsView->vexNumber()));
    ui->LinesNum->setText(QString::number(ui->graphicsView->linesNumber()));
    if (ui->graphicsView->IsDirected()) {
        ui->Detail->setText("Directed");
    }
    else {
        ui->Detail->setText("UnDirected");
    }
}

void MainWindow::on_setDirectedButton_clicked()
{
    ui->graphicsView->setDirected();
    infoUpdate();
}

void MainWindow::on_setUnDirectedButton_clicked()
{
    ui->graphicsView->setUnDirected();
    infoUpdate();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    infoUpdate();
    QMainWindow::mousePressEvent(event);
}

void MainWindow::on_DelButton_clicked()
{
    ui->graphicsView->removeSelectItem();
    infoUpdate();
}


void MainWindow::on_BFSButton_clicked()
{
    ui->graphicsView->BFS();
}

void MainWindow::on_setClearButton_clicked()
{
    ui->graphicsView->clearView();
}

void MainWindow::on_DFSButton_clicked()
{
    ui->graphicsView->DFS();
}


void MainWindow::on_AdjTableButton_clicked()
{
    ui->graphicsView->buildAdjtable();
}



void MainWindow::on_AdjMatrixButton_clicked()
{
    ui->graphicsView->buildAdjMatrix();
}

void MainWindow::on_KruskalButton_clicked()
{
    ui->graphicsView->Kruskal();
}


void MainWindow::on_DijkstraButton_clicked()
{
    ui->graphicsView->Dijkstra();
}

void MainWindow::on_PrimButton_clicked()
{
    ui->graphicsView->Prim();
}

void MainWindow::on_FloydButton_clicked()
{
    ui->graphicsView->Floyd();
}
