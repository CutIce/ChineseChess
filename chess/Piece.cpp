#include "Piece.h"
#include "Board.h"


Piece::Piece()
{
    selected = -1;
    move     = -1;
}

QPoint Piece::getPoint() {
    QPoint ret;
    ret.setX( (this->col) * dist);
    ret.setY( (this->row) * dist);
    return ret;
}


QString Piece::getType() {
    if (color == red) {
        if (type == pawn)       return "兵";
        if (type == knight)     return "馬";
        if (type == rook)       return "車";
        if (type == cannon)     return "炮";
        if (type == bishop)     return "相";
        if (type == advisor)    return "仕";
        if (type == king)       return "帅";
    } else {
        if (type == pawn)       return "卒";
        if (type == knight)     return "马";
        if (type == rook)       return "車";
        if (type == cannon)     return "砲";
        if (type == bishop)     return "象";
        if (type == advisor)    return "士";
        if (type == king)       return "将";
    }
}

void Piece::init(int id) {
    // 0 king        16
    // 1 2  rook     17 18
    // 3 4  knight   19 20
    // 5 6  cannon   21 22
    // 7 8  advisor  23 24
    // 9 10 bishop   25 26
    // 11 - 15 pawn  27 - 31
//    this->id = id;

//    color = (id < 16) ? red : blue;
//    assert(id < 32 && id > 0);
//    if (id == 0 || id == 16) type = king;
//    else if (id == 1 || id == 2 || id == 17 || id == 18) type = rook;
//    else if (id == 3 || id == 4 || id == 19 || id == 20) type = knight;
//    else if (id == 5 || id == 6 || id == 21 || id == 22) type = cannon;
//    else if (id == 7 || id == 8 || id == 23 || id == 24) type = advisor;
//    else if (id == 9 || id == 10 || id == 25 || id == 26) type = bishop;
//    else if (id < 32) {
//        type = pawn;
//    }
}
