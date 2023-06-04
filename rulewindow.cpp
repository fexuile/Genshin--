#include "rulewindow.h"
#include "ui_rulewindow.h"

rulewindow::rulewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rulewindow)
{
    ui->setupUi(this);

    ui->backButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->backButton->move(1200,850);
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);

    connect(ui->backButton,&QPushButton::clicked,[=](){
        ClickSound->play();
        emit closeWindow();
    });
}

rulewindow::~rulewindow()
{
    delete ui;
}

void rulewindow::paintEvent(QPaintEvent* event){
    QPainter Painter(this);
    Painter.setBrush(QColor(0,0,0,200));
    Painter.drawRect(0,0,MAX_WINDOWS_WEIGHT,MAX_WINDOWS_HEIGHT);
    Painter.drawPixmap(0,0,MAX_WINDOWS_WEIGHT,MAX_WINDOWS_HEIGHT,QPixmap(":/image/images/Rule.png"));
}
