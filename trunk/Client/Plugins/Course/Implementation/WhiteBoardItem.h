#ifndef WHITEBOARDITEM_H
#define WHITEBOARDITEM_H

#include <QList>

class WhiteBoardItem
{
public:
    WhiteBoardItem(int id, int x, int y, int width, int height, bool isDocked)
        : id(id), x(x), y(y), width(width), height(height), isDocked(isDocked)
    {
    }

    int getId() const { return id; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool docked() const {return isDocked; }

private:
    int id;
    int x;
    int y;
    int width;
    int height;
    bool isDocked;
};

typedef QList<WhiteBoardItem> WhiteBoardItemList;

#endif // WHITEBOARDITEM_H
