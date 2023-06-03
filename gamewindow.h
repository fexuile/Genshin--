#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

namespace Ui {
class gamewindow;
}

class gamewindow : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow(int level = 0, QWidget *parent = nullptr);
    ~gamewindow();

private:
    Ui::gamewindow *ui;
};

#endif // GAMEWINDOW_H
