#include "vexdetail.h"
#include "ui_vexdetail.h"

VexDetail::VexDetail(VexItem *vex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VexDetail)
{
    ui->setupUi(this);
    this->vex = vex;

    ui->NoText->setText(QString::number(vex->No()));
    ui->TagText->setText(vex->getTag());
    if (vex->getDist() != -1) {
        ui->DistText->setText(QString::number(vex->getDist()));
    }
    if (vex->getPre() != -1) {
        ui->PrevText->setText(QString::number(vex->getPre()));
    }
    if (vex->getStart() != -1) {
        ui->StartText->setText(QString::number(vex->getStart()));
    }

}

VexDetail::~VexDetail()
{
    delete ui;
}

void VexDetail::on_saveButton_clicked()
{
    vex->setTag(ui->TagText->text());
    vex->update();
    this->close();
}

void VexDetail::on_CancelButton_clicked()
{
    this->close();
}
