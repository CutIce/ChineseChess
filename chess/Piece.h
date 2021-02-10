#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QPoint>


// 将 士 相 马 车 炮 兵
typedef enum {king = 0, advisor, bishop, knight, rook, cannon, pawn} Type;
typedef enum {red, black} Color;


class Piece
{
public:
    int row;
    int col;
    bool dead;
    Type type;
    Color color;
    int id;
    int selected;
    int move;
    Piece();
    QPoint getPoint();
    QString getType();
    void init(int id);

};

#endif // PIECE_H
