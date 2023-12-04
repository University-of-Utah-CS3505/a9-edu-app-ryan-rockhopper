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
    /// @brief The constructor for our Pop-up object
    explicit PopUp(QWidget *parent = nullptr);
    /// @brief The destructor for our Pop-up object
    ~PopUp();

signals:
    /// @brief This signal is called when the pop-up closes
    void popupClosed();
private:
    Ui::PopUp *ui;

private slots:
    /// @brief this slot closes the pop-up when the yes button is clicked
    void on_yesButton_clicked();
    /// @brief this slot changes the pop-up image when the no button is clicked
    void on_noButton_clicked();
};

#endif // POPUP_H
