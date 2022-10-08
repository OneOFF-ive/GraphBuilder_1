#include "selectend.h"
#include "ui_selectend.h"
#include <QIntValidator>

SelectEnd::SelectEnd(MyGraphicsView *view, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectEnd)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0, view->vexNumber(), this));
}

SelectEnd::~SelectEnd()
{
    delete ui;
}

int SelectEnd::end() const
{
    if (ui->lineEdit->text() == "") {
        return -1;
    }
    else {
        return ui->lineEdit->text().toInt();
    }
}

void SelectEnd::on_saveButton_clicked()
{
    this->close();
}

void SelectEnd::on_cancelButton_clicked()
{
    ui->lineEdit->setText("");
    this->close();
}
