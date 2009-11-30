#ifndef EDTSCENE_H
#define EDTSCENE_H

#include <QGraphicsScene>
#include <QMouseEvent>
class EDTScene : public QGraphicsScene
{
    Q_OBJECT
public:
    EDTScene();

private:
    void addFullDayBGtoScene(int pos, int wid);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* e);
};

#endif // EDTSCENE_H
