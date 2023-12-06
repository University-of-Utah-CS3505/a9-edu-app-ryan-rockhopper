#include "meme.h"
#include "ui_meme.h"
#include <QRegularExpression>

meme::meme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::meme)
{
    ui->setupUi(this);
}

meme::~meme()
{
    delete ui;
}

void meme::on_lineEdit_ratingChanged()
{
    QRegularExpression regex("^[0-9]$");
    if (regex.match(ui->lineEdit->text()).hasMatch())
    {
        this->close();
        emit popupClosed();
        ui->lineEdit->clear();
    }
}
