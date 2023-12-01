#ifndef POPUP_H
#define POPUP_H

#include <QWidget>

namespace Ui {
class PopUp;
}

class PopUp : public QWidget
{
    Q_OBJECT

public:
    explicit PopUp(QWidget *parent = nullptr);
    ~PopUp();

signals:
    void popupClosed();
private:
    Ui::PopUp *ui;

private slots:
    void on_yesButton_clicked();
    void on_noButton_clicked();
};

#endif // POPUP_H
