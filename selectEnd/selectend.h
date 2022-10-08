#ifndef SELECTEND_H
#define SELECTEND_H

#include <QDialog>
#include "myGraphicsView/mygraphicsview.h"

namespace Ui {
class SelectEnd;
}

class SelectEnd : public QDialog
{
    Q_OBJECT

public:
    explicit SelectEnd(MyGraphicsView *view, QWidget *parent = nullptr);
    ~SelectEnd();

    int end() const;

private:
    Ui::SelectEnd *ui;

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();


};

#endif // SELECTEND_H
