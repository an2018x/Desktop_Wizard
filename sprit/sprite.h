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
public slots:
    void change();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // SPRITE_H
