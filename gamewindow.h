#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include "role.h"

namespace Ui {
class gamewindow;
}

class gamewindow : public QWidget
{
    Q_OBJECT

public:
    int level, mouse_x, mouse_y, clicked;
    explicit gamewindow(int LEVEL = 1, QWidget *parent = nullptr);
    void set_player();
    ~gamewindow();
    void mousePressEvent(QMouseEvent *event) override;
    bool game_end();
    bool checkround();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void closeWindow(void);

private:
    Ui::gamewindow *ui;
    QLabel *Background;
    Monster* Boss;
    Player* player[4];
};

#endif // GAMEWINDOW_H
