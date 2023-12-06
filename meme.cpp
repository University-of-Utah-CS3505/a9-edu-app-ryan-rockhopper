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
    return num >= 1 && num <= 10;
}

void meme::on_lineEdit_returnPressed()
{
    bool conversionSuccess;
    int textValue = ui->lineEdit->text().toInt(&conversionSuccess);
    if (conversionSuccess && isNumberInRange(textValue))
    {
        this->close();
        emit popupClosed();
        ui->lineEdit->clear();
    }
}
