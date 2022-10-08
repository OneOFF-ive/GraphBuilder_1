#include "linedetail.h"
#include "ui_linedetail.h"

LineDetail::LineDetail(LineItem *line, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineDetail)
{
    ui->setupUi(this);
    this->line = line;

    ui->NoText_2->setText(QString::number(line->No()));
    ui->WeightText->setText(QString::number(line->getWeight()));
    ui->StartText->setText(line->getStartVex()->getTag());
    ui->EndText->setText(line->getEndVex()->getTag());
}

LineDetail::~LineDetail()
{
    delete ui;
}

void LineDetail::on_saveButton_clicked()
{
    line->setWeight(ui->WeightText->text().toInt());
    line->update();
    this->close();
}

void LineDetail::on_CancelButton_clicked()
{
    this->close();
}
