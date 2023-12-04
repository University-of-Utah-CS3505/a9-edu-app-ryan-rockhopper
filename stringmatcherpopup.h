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
    /// @brief This is the constructor for the String matching pop-up
    explicit StringMatcherPopup(QWidget *parent = nullptr);
    /// @brief This is the destructor for our String matching Pop-up
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

signals:
    /// @brief This is the signal that the pop-up sends when it is closed
    void popupClosed();

public slots:
    /// @brief This is the slat that gets called when the text the user typed in changes
    void on_lineEdit_textChanged();
    /// @brief This is the slot that gets called when the pop-up is spawned to change the word the user should match
    void changeText();
};

#endif // STRINGMATCHERPOPUP_H
