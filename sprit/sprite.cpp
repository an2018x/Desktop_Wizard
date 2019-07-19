#include "sprite.h"

Sprite::Sprite(QWidget *parent)
    : QWidget(parent)
{

    setWindowFlags(Qt::Tool);
    move(1200,600);
    act1 = new QAction(tr("你好！我是你的桌面精灵小圆"), this);
    act2 = new QAction(tr(""), this);
    act3 = new QAction(tr(""), this);
    menu=new QMenu(this);
    createWidget();
    createBtnWidget();
    createTrayIcon();
    menu->addAction(wact);

    menu->addAction(act1); //添加菜单项1
    menu->addAction(act2); //添加菜单项2
    menu->addAction(act3); //最小化

    pix=new QPixmap();
    pix->load(":/img/attack/0000.png");
    resize(pix->size());
    setMask(pix->mask());

    menu2 = new QMenu(this);
    menu2->addAction(act1);
    menu2->addAction(act2);
    menu2->addAction(act4);

    step=0;
    timer=new QTimer(this);
    timer->start(300);
    connect(timer,SIGNAL(timeout()),this,SLOT(change()));
    connect(btn2,&QPushButton::clicked,[=](){this->close();delete trayIcon;});
    connect(btn3,&QPushButton::clicked,[=](){this->hide();ismin=true;});

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
        //menu->show();
        menu->exec(QCursor::pos());
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

void Sprite::mininum()
{
    if(ismin == false)
    {
        this->hide();
        ismin = true;
    }
}

void Sprite::InitUI()
{


    label1=new QLabel;
    label1->setFixedSize(60,60);
    QPixmap pix(":/img/others/icon.png");
    label1->setScaledContents(true);
    label1->setPixmap(pix);
    widgetMenu=new QWidget(this);
    layout1=new QVBoxLayout;
    layout1->addWidget(label1,0,Qt::AlignLeft);
    layout1->setSpacing(5);
    widgetMenu->setLayout(layout1);
    wact=new QWidgetAction(menu);
    wact->setDefaultWidget(widgetMenu);


}

void Sprite::TrayIconAction(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
    {
        if(ismin == true)
        {
            this->showNormal();
            ismin = false;
        }else
        {
            this->hide();
            ismin = true;
        }
    }
}

void Sprite::exit()
{

    widgetMenu2=new QWidget(this);
    btn1=new QPushButton(QIcon(":/img/others/about.png"),tr(""));
    btn2=new QPushButton(QIcon(":/img/others/exit.png"),tr(""));
    btn3=new QPushButton(QIcon(":/img/others/mini.png"),tr(""));
    btn1->setStyleSheet("background:transparent");
    btn2->setStyleSheet("background:transparent");
    btn3->setStyleSheet("background:transparent");
    btn1->setFixedSize(25,25);
    btn2->setFixedSize(25,25);
    btn3->setFixedSize(25,25);
    QHBoxLayout *layoutH=new QHBoxLayout;
    layoutH->addWidget(btn1,0,Qt::AlignCenter);
    layoutH->addWidget(btn2,0,Qt::AlignCenter);
    layoutH->addWidget(btn3,0,Qt::AlignCenter);
    layoutH->setSpacing(5);
    widgetMenu2->setLayout(layoutH);
    wact2=new QWidgetAction(menu);
    wact2->setDefaultWidget(widgetMenu2);

}
void Sprite::createTrayIcon()
{
    trayIcon=new QSystemTrayIcon(this);
    QIcon icon(":/img/others/icon.png");
    trayIcon->setIcon(icon);
    trayIcon->show();
    trayIcon->setContextMenu(menu);

    connect(trayIcon,&QSystemTrayIcon::activated,this,&Sprite::TrayIconAction);

}
void Sprite::TrayIconAction(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
    {
        if(ismin == true)
        {
            this->show();
            ismin = false;
        }else
        {
            this->hide();
            ismin = true;
        }
    }
}
