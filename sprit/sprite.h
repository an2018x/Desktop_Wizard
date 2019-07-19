#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QImage>
#include <QBitmap>
#include <QPaintEvent>
#include <QAction>
#include <QMenu>
#include <QFile>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidgetAction>
#include <QPushButton>
#include <QSystemTrayIcon>

class Sprite : public QWidget
{
    Q_OBJECT

public:
    Sprite(QWidget *parent = 0);

    void createWidget();
    void createBtnWidget();
    void TrayIconAction(QSystemTrayIcon::ActivationReason reason);
    
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
    QAction *act3;
    QFile *qssFile;
    QLabel *label1;
    QLabel *label2;
    QVBoxLayout *layout1;
    QWidget *widgetMenu;
    QWidget *widgetMenu2;
    QWidgetAction *wact;
    QWidgetAction *wact2;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QSystemTrayIcon *trayIcon;
    bool ismin;

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
    void createTrayIcon();


};

#endif // SPRITE_H
