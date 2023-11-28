#include "popup.h"
#include "ui_popup.h"

PopUp::PopUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopUp)
{
    ui->setupUi(this);
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::on_yesButton_clicked()
{
    this->close();
}

void PopUp::on_noButton_clicked()
{
    ui->neutralFace->hide();
}
