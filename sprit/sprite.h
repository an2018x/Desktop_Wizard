#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QImage>
#include <QBitmap>
#include <QPaintEvent>
#include <QAction>
#include <QMenu>
#include<QSystemTrayIcon>

class Sprite : public QWidget
{
    Q_OBJECT

public:
    Sprite(QWidget *parent = 0);
    ~Sprite();

private:
    QPixmap *pix;
    QImage *img;
    int step;
    QTimer *timer;
    bool isDrag;
    QPoint m_position;
    QMenu *menu;
    QAction *act1;
    QAction *act2;
    QAction *act3;  //最小化窗口
    QAction *act4;  //关闭窗口
    bool ismin;
    QMenu *menu2;

public slots:
    void change();
    void mininum(); //最小化
    void TrayIconAction(QSystemTrayIcon::ActivationReason reason);
    void InitUI();  //创建托盘图标
    void exit();

private:
    QSystemTrayIcon *tray;  //托盘类


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // SPRITE_H
