#ifndef MEME_H
#define MEME_H

#include <QWidget>

namespace Ui {
class meme;
}

class meme : public QWidget
{
    Q_OBJECT

public:
    explicit meme(QWidget *parent = nullptr);
    ~meme();
    bool isNumberInRange(int number);

private:
    Ui::meme *ui;

signals:
    /// @brief This signal is called when the pop-up closes
    void popupClosed();

public slots:
    void on_lineEdit_textChanged();

};

#endif // MEME_H
