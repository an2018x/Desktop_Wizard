#include "sprite.h"
#include <QDebug>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
Sprite::Sprite(QWidget *parent)
    : QWidget(parent)
{
    move(1200,600);
    act1 = new QAction(tr("你好！我是你的桌面精灵"), this);
    act2 = new QAction(tr("开发中"), this);
    act3 = new QAction(tr("开发中"), this);
    menu=new QMenu(this);
    createWidget();
    createBtnWidget();
    menu->addAction(wact);
    menu->addAction(act1); //添加菜单项1
    menu->addAction(act2); //添加菜单项2
    menu->addAction(act3);
    menu->addAction(wact2);
    qssFile=new QFile(":/qss/menu.qss",this);
    qssFile->open(QFile::ReadOnly);
    QString style=tr(qssFile->readAll());
    menu->setStyleSheet(style);
    qssFile->close();
    pix=new QPixmap();
    pix->load(":/img/attack/0000.png");
    resize(pix->size());
    setMask(pix->mask());
    step=0;
    timer=new QTimer(this);
    timer->start(300);
    connect(timer,SIGNAL(timeout()),this,SLOT(change()));
}

Sprite::~Sprite()
{

}

void Sprite::change()
{
    QString name;
    step++;
    if(step>8)  step=0;
    switch (step) {
    case 0: name=":/img/attack/0000.png";break;
    case 1: name=":/img/attack/0001.png";break;
    case 2: name=":/img/attack/0002.png";break;
    case 3: name=":/img/attack/0003.png";break;
    case 4: name=":/img/attack/0004.png";break;
    case 5: name=":/img/attack/0005.png";break;
    case 6: name=":/img/attack/0006.png";break;
    case 7: name=":/img/attack/0007.png";break;
    case 8: name=":/img/attack/0008.png";break;
    default:break;
    }
    pix->load(name);
    resize(pix->size());
    setMask(QBitmap(pix->mask()));
    update();
}
void Sprite::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *pix);
}
void Sprite::mousePressEvent(QMouseEvent *event)
{
    setCursor( Qt::ClosedHandCursor);
    if(event->button() == Qt::LeftButton)
    {
        isDrag = true;
        m_position = event->globalPos() - this->pos();

    }
    if(event->button() == Qt::RightButton)
    {
        menu->exec(pos()+QPoint(0,100));
    }
}


void Sprite::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag && (e->buttons() == Qt::LeftButton))
    {
        move(e->globalPos() - m_position);
    }
}

void Sprite::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor( Qt::OpenHandCursor);
    isDrag = false;
}

void Sprite::createWidget()
{
    label1=new QLabel(tr("你好！很高兴见到你！"));
    widgetMenu=new QWidget(this);
    layout1=new QVBoxLayout;
    layout1->addWidget(label1,0,Qt::AlignLeft);
    layout1->setSpacing(5);
    widgetMenu->setLayout(layout1);
    wact=new QWidgetAction(menu);
    wact->setDefaultWidget(widgetMenu);

}
void Sprite::createBtnWidget()
{
    widgetMenu2=new QWidget(this);
    btn1=new QPushButton(QIcon(":/img/others/about.png"),tr(""));
    btn2=new QPushButton(QIcon(":/img/others/exit.png"),tr(""));
    btn1->setStyleSheet("background:transparent");
    btn2->setStyleSheet("background:transparent");
    btn1->setFixedSize(25,25);
    btn2->setFixedSize(25,25);
    QHBoxLayout *layoutH=new QHBoxLayout;
    layoutH->addWidget(btn1,0,Qt::AlignCenter);
    layoutH->addWidget(btn2,0,Qt::AlignCenter);
    layoutH->setSpacing(5);
    widgetMenu2->setLayout(layoutH);
    wact2=new QWidgetAction(menu);
    wact2->setDefaultWidget(widgetMenu2);
}
