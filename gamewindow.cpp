#include "gamewindow.h"
#include "ui_gamewindow.h"

gamewindow::gamewindow(int level, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);

}

gamewindow::~gamewindow()
{
    delete ui;
}
