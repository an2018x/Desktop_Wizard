#include "sprite.h"

Sprite::Sprite(QWidget *parent)
    : QWidget(parent)
{
    ismin = false;

    move(1200,600);
    act1 = new QAction(tr("开发中"), this);
    act2 = new QAction(tr("开发中"), this);
    act3 = new QAction(tr("最小化"),this);
    act4 = new QAction(tr("退出"),this);

    menu=new QMenu(this);
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
    connect(act3,&QAction::triggered,this,&Sprite::mininum);

    InitUI();

    //设置任务栏为隐藏
    setWindowFlags(Qt::Tool);
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
    //暂时用这张图当logo
    QPixmap logo(":/img/attack/logo.png");
    setWindowIcon(QIcon(logo));

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(logo));
    tray->show();

    tray->setContextMenu(menu2);

    connect(tray,&QSystemTrayIcon::activated,this,&Sprite::TrayIconAction);
    connect(act4,&QAction::triggered,this,&Sprite::exit);

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
    close();
    delete tray;
}
