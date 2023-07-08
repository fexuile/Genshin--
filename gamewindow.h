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
    my_genshin *game;
    int level;
    explicit gamewindow(int LEVEL = 1, QWidget *parent = nullptr);
    void set_player();
    void A_attack();
    void R_attack();
    void update(int level);
    void Boss_attack();
    void GameEnd(int flag);
    ~gamewindow();

protected:
    void paintEvent(QPaintEvent *event) override;
signals:
    void closeWindow(void);
    void closeAll(void);
private:
    Ui::gamewindow *ui;
    QLabel *Background;
};

#endif // GAMEWINDOW_H
