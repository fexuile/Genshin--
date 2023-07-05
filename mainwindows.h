#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QMainWindow>
#include <QMovie>
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QSound>
#include <QTimer>

#include "config.h"
#include "rulewindow.h"
#include "gamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindows; }
QT_END_NAMESPACE

class mainwindows : public QMainWindow
{
    Q_OBJECT
public:
    mainwindows(QWidget *parent = nullptr);
    ~mainwindows();

private:
    Ui::mainwindows *ui;
    QLabel *Background;
    QSound *mainSound,*MainSound;
    rulewindow *Rule_Page;
    gamewindow *New_Game, *Load_Game;
};
#endif // MAINWINDOWS_H
