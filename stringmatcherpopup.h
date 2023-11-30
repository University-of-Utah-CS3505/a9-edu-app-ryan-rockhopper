#ifndef STRINGMATCHERPOPUP_H
#define STRINGMATCHERPOPUP_H

#include <QWidget>

namespace Ui {
class StringMatcherPopup;
}

class StringMatcherPopup : public QWidget
{
    Q_OBJECT

public:
    explicit StringMatcherPopup(QWidget *parent = nullptr);
    ~StringMatcherPopup();

private:
    Ui::StringMatcherPopup *ui;
    std::vector<QString> words
    {
        "hey",
        "really",
        "goodbye",
        "Unbelievable"
    };

public slots:
    void on_lineEdit_textChanged();
    void changeText();
};

#endif // STRINGMATCHERPOPUP_H
