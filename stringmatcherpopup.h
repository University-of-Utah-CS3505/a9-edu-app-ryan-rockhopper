#ifndef STRINGMATCHERPOPUP_H
#define STRINGMATCHERPOPUP_H

#include <QWidget>
#include <string>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QRandomGenerator>

using std::string;
using std::vector;

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
    vector<QString> words
    {
        "hi",
        "yo!",
        "hey",
        "wow",
        "sup!",
        "Nope",
        "wait.",
        "Sorry",
        "NoWay!",
        "really?",
        "Wassup?",
        "goodbye",
        "Surprise!",
        "Fantastic",
        "Incredible",
        "Absolutely.",
        "Unbelievable",
        "Outstanding!",
        "congratulations"
    };

    vector<QString> dictionaryEntries;

    /// @brief Opens the dictionary file and reads in each word into a vector
    /// @param fileName is the name of the dictionary.txt file
    void readDictionaryFile(QString fileName);

signals:
    /// @brief This is the signal that the pop-up sends when it is closed
    void popupClosed();

public slots:
    /// @brief This is the slot that gets called when the text the user typed in changes
    void on_lineEdit_textChanged();

    /// @brief This is the slot that gets called when the pop-up is spawned to change the word the user should match
    void changeText();
};

#endif // STRINGMATCHERPOPUP_H
