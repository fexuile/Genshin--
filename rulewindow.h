#ifndef RULEWINDOW_H
#define RULEWINDOW_H

#include <QWidget>
#include "config.h"
#include <QSound>
#include <QPainter>

namespace Ui {
class rulewindow;
}

class rulewindow : public QWidget
{
    Q_OBJECT

public:
    explicit rulewindow(QWidget *parent = nullptr);
    ~rulewindow();
protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void closeWindow(void);

private:
    Ui::rulewindow *ui;
};

#endif // RULEWINDOW_H
