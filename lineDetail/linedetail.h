#ifndef LINEDETAIL_H
#define LINEDETAIL_H

#include <QDialog>
#include "lineItem/lineitem.h"

namespace Ui {
class LineDetail;
}

class LineDetail : public QDialog
{
    Q_OBJECT

public:
    explicit LineDetail(LineItem *line, QWidget *parent = nullptr);
    ~LineDetail();

private slots:
    void on_saveButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::LineDetail *ui;
    LineItem *line;
};

#endif // LINEDETAIL_H
