#ifndef VEXDETAIL_H
#define VEXDETAIL_H

#include <QDialog>
#include "vexItem/vexitem.h"

namespace Ui {
class VexDetail;
}

class VexDetail : public QDialog
{
    Q_OBJECT

public:
    explicit VexDetail(VexItem *vex, QWidget *parent = nullptr);
    ~VexDetail();

private slots:
    void on_saveButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::VexDetail *ui;
    VexItem *vex;
};

#endif // VEXDETAIL_H
