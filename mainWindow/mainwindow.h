#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qevent.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void infoUpdate();

    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_setDirectedButton_clicked();

    void on_setUnDirectedButton_clicked();

    void on_DelButton_clicked();

    void on_BFSButton_clicked();

    void on_setClearButton_clicked();

    void on_DFSButton_clicked();

    void on_AdjTableButton_clicked();

    void on_AdjMatrixButton_clicked();

    void on_KruskalButton_clicked();

    void on_DijkstraButton_clicked();

    void on_PrimButton_clicked();

    void on_FloydButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
