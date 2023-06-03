#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QMainWindow>
#include <QMovie>
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QSound>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindows; }
QT_END_NAMESPACE

class mainwindows : public QMainWindow
{
    Q_OBJECT
public:
    mainwindows(QWidget *parent = nullptr);
    ~mainwindows();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mainwindows *ui;
    QSound *mainSound;
};
#endif // MAINWINDOWS_H
