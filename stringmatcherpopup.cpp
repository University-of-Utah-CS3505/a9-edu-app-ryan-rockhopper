#include "stringmatcherpopup.h"
#include "ui_stringmatcherpopup.h"

StringMatcherPopup::StringMatcherPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringMatcherPopup)
{
    ui->setupUi(this);
}

StringMatcherPopup::~StringMatcherPopup()
{
    delete ui;
}

void StringMatcherPopup::on_lineEdit_textChanged()
{
    if (ui->label->text() == ui->lineEdit->text()) this->close();
}

void StringMatcherPopup::changeText()
{
    int randomIndex = rand() % words.size();
    ui->label->setText(words[randomIndex]);
}
