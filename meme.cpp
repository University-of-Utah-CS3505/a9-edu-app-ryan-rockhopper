#include "meme.h"
#include "ui_meme.h"

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

bool meme::isNumberInRange(int num)
{
    return num >= 0 && num <= 9;
}

void meme::on_lineEdit_textChanged()
{
    int textValue = ui->lineEdit->text().toInt() - 1;
    if (isNumberInRange(textValue))
    {
        this->close();
        emit popupClosed();
        ui->lineEdit->clear();
    }
}
