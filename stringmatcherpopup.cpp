#include "stringmatcherpopup.h"
#include "ui_stringmatcherpopup.h"

StringMatcherPopup::StringMatcherPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringMatcherPopup)
{
    ui->setupUi(this);
    readDictionaryFile(":/safedict_complex.txt");
}

StringMatcherPopup::~StringMatcherPopup()
{
    delete ui;
}

void StringMatcherPopup::on_lineEdit_textChanged()
{
    if (ui->label->text() == ui->lineEdit->text())
    {
        this->close();
        emit popupClosed();
        ui->lineEdit->clear();
    }
}

void StringMatcherPopup::changeText()
{
    if(QRandomGenerator::global()->generate() % 2 == 0 || dictionaryEntries.empty())
    {
        int randomIndex = QRandomGenerator::global()->generate() % words.size();
        ui->label->setText(words.at(randomIndex));
    }
    else
    {
        int randomIndex = QRandomGenerator::global()->generate() % dictionaryEntries.size();
        ui->label->setText(dictionaryEntries.at(randomIndex));
    }
}

void StringMatcherPopup::readDictionaryFile(QString fileName)
{
    QString entry;
    QFile dictionary(fileName);

    if(!dictionary.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error opening dictionary.txt";
        return;
    }

    QTextStream in(&dictionary);

    while(!in.atEnd())
    {
        entry = in.readLine();
        dictionaryEntries.push_back(entry);
    }

    dictionary.close();
}
