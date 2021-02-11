#include "Board.h"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget *parent) : QWidget(parent)
{
    mycolor = red;
    int i = 0;
    setPiece(i++, 1, 5, 0, red, king); // 0
    setPiece(i++, 1, 1, 0, red, rook); // 1
    setPiece(i++, 1, 9, 0, red, rook); // 2

    setPiece(i++, 1, 2, 0, red, knight);// 3
    setPiece(i++, 1, 8, 0, red, knight);// 4

    setPiece(i++, 3, 2, 0, red, cannon);// 5
    setPiece(i++, 3, 8, 0, red, cannon);// 6

    setPiece(i++, 1, 3, 0, red, bishop);// 7
    setPiece(i++, 1, 7, 0, red, bishop);// 8

    setPiece(i++, 1, 4, 0, red, advisor);// 9
    setPiece(i++, 1, 6, 0, red, advisor);// 10

    for (;i<16;++i) setPiece(i, 4, 2*(i-11)+1, 0, red, pawn); // 11 - 15


    setPiece(i++, 10, 5, 0, black, king); // 16
    setPiece(i++, 10, 1, 0, black, rook); // 17
    setPiece(i++, 10, 9, 0, black, rook); // 18

    setPiece(i++, 10, 2, 0, black, knight);// 19
    setPiece(i++, 10, 8, 0, black, knight);// 20

    setPiece(i++, 8, 2, 0, black, cannon);// 21
    setPiece(i++, 8, 8, 0, black, cannon);// 22

    setPiece(i++, 10, 3, 0, black, bishop);// 23
    setPiece(i++, 10, 7, 0, black, bishop);// 24

    setPiece(i++, 10, 4, 0, black, advisor);// 25
    setPiece(i++, 10, 6, 0, black, advisor);// 26

    for (;i<32;++i) setPiece(i, 7, 2*(i-27)+1, 0, black, pawn); // 27 - 31

    selected = -1;
    rotate = false;
}

inline void Board::setPiece(int id, int row, int col, bool dead, Color c, Type type) {
    piece[id].row = row;
    piece[id].col = col;
    piece[id].dead = dead;
    piece[id].color = c;
    piece[id].type = type;
}

void Board::drawPiece(QPainter* p, int id){
    if (piece[id].dead) return;
    QFont fontPiece("黑体", 18,QFont::Bold, false);
    p->setFont(fontPiece);
    if (id == selected) p->setBrush(QBrush(Qt::gray));
    else    p->setBrush(QBrush(QColor(255, 255, 0)));

    QPoint tem = piece[id].getPoint();
    QRect rect = QRect(tem.x() - r_chess , tem.y() - r_chess, 2*r_chess, 2*r_chess);
    p->drawEllipse(tem, (int)r_chess, (int)r_chess);

    if (piece[id].color == red) p->setPen(Qt::red);
    else p->setPen(Qt::black);
    p->drawText(rect, piece[id].getType(), QTextOption(Qt::AlignCenter));
}

void Board::drawFineLine(QPainter *p, int i, int j) {
    if (i == 1) {
        // 右上方
        p->drawLine(QPointF(i*dist + space, j*dist - fineLinelength), QPointF(i*dist + space, j*dist - space));
        p->drawLine(QPointF(i*dist + space, j*dist - space), QPointF(i*dist + fineLinelength, j*dist - space));
        // 右下方
        p->drawLine(QPointF(i*dist + space, j*dist + fineLinelength), QPointF(i*dist + space, j*dist + space));
        p->drawLine(QPointF(i*dist + space, j*dist + space), QPointF(i*dist + fineLinelength, j*dist + space));

    } else if (i == 9) {
        // 左上方
        p->drawLine(QPointF(i*dist - space, j*dist - fineLinelength), QPointF(i*dist - space, j*dist - space));
        p->drawLine(QPointF(i*dist - space, j*dist - space), QPointF(i*dist - fineLinelength, j*dist - space));
        // 左下方
        p->drawLine(QPointF(i*dist - space, j*dist + fineLinelength), QPointF(i*dist - space, j*dist + space));
        p->drawLine(QPointF(i*dist - space, j*dist + space), QPointF(i*dist - fineLinelength, j*dist + space));
    } else {
        // 右上方
        p->drawLine(QPointF(i*dist + space, j*dist - fineLinelength), QPointF(i*dist + space, j*dist - space));
        p->drawLine(QPointF(i*dist + space, j*dist - space), QPointF(i*dist + fineLinelength, j*dist - space));
        // 右下方
        p->drawLine(QPointF(i*dist + space, j*dist + fineLinelength), QPointF(i*dist + space, j*dist + space));
        p->drawLine(QPointF(i*dist + space, j*dist + space), QPointF(i*dist + fineLinelength, j*dist + space));
        // 左上方
        p->drawLine(QPointF(i*dist - space, j*dist - fineLinelength), QPointF(i*dist - space, j*dist - space));
        p->drawLine(QPointF(i*dist - space, j*dist - space), QPointF(i*dist - fineLinelength, j*dist - space));
        // 左下方
        p->drawLine(QPointF(i*dist - space, j*dist + fineLinelength), QPointF(i*dist - space, j*dist + space));
        p->drawLine(QPointF(i*dist - space, j*dist + space), QPointF(i*dist - fineLinelength, j*dist + space));
    }
}

void Board::paintEvent(QPaintEvent *event) {
    QPainter paint(this);

    // 画棋盘
    for (int i = 1; i < 11; ++i) {
        paint.drawLine(QPoint(dist,i*dist), QPoint(9*dist, i*dist));
    }

    for (int i = 1; i < 10; ++i) {
        if (i == 1 || i == 9 )
            paint.drawLine(QPoint(i*dist, dist), QPoint(i*dist, 10*dist));
        else{
            paint.drawLine(QPoint(i*dist, dist), QPoint(i*dist, 5*dist));
            paint.drawLine(QPoint(i*dist, 6*dist), QPoint(i*dist, 10*dist));
            }
    }

    // 画炮的横线
    drawFineLine(&paint, 2, 3);
    drawFineLine(&paint, 2, 8);
    drawFineLine(&paint, 8, 3);
    drawFineLine(&paint, 8, 8);

    // 画兵旁边的横线
    for (int i = 1; i < 10; i += 2) {
        drawFineLine(&paint, i, 4);
        drawFineLine(&paint, i, 7);
    }

    // 画宫格
    paint.drawLine(QPoint(4*dist, dist), QPoint(6*dist, 3*dist));
    paint.drawLine(QPoint(4*dist, 3*dist), QPoint(6*dist, dist));
    paint.drawLine(QPoint(4*dist, 8*dist), QPoint(6*dist, 10*dist));
    paint.drawLine(QPoint(4*dist, 10*dist), QPoint(6*dist, 8*dist));

    for (int i = 0; i<32; ++i)
         drawPiece(&paint, i);
}


void Board::mousePressEvent(QMouseEvent *event) {

}

void Board::mouseReleaseEvent(QMouseEvent *event) {
    QPoint p = event->pos();

    int moveto_prow = (int) (p.y() + 0.5*dist) / dist;
    int moveto_pcol = (int) (p.x() + 0.5*dist) / dist;

    if (moveto_prow < 1 || moveto_prow > 10 || moveto_pcol < 1 || moveto_pcol > 9) {selected = -1; return;}
    int moveto = isPiece(moveto_prow, moveto_pcol);

    if (selected == -1) {
        if (moveto < 0 || moveto > 32) {selected = -1; return;}
        selected = moveto;
        update();
    } else {
        bool moveFlag = checkMove(selected, moveto_prow, moveto_pcol, moveto);
        if (moveFlag) {
            if (moveto != -1) piece[moveto].dead = true;
            piece[selected].row = moveto_prow;
            piece[selected].col = moveto_pcol;
            selected = -1;
            update();
        } else { selected = -1;update();}
    }
}


inline int Board::isMyPiece(int row, int col) {
    for (int i = 0; i < 32; ++i) {
        if (piece[i].row == row && piece[i].col == col && piece[i].color == mycolor && !piece[i].dead) return i;
        if (piece[i].row == row && piece[i].col == col && !piece[i].dead) return i;
    }
    return -1;
}

inline int Board::isPiece(int row, int col) {
    for (int i = 0; i < 32; ++i) {
        if (piece[i].row == row && piece[i].col == col && !piece[i].dead) return i;
    }
    return -1;
}

// 从一个棋子的角度可以走
// 须在棋盘层面考虑己方子占位和蹩马腿、卡象眼等
inline bool Board::checkMoveKing(int sel_id, int to_row, int to_col) {
    Piece sel = piece[sel_id];
    // 行数之差为0，>1,1
    int tmp1 = abs(sel.row - to_row);
    int tmp2 = abs(sel.col - to_col);
    if (tmp1 > 1 || tmp2 > 1 || (tmp1 == 1 && tmp2 ==1)) return 0;
    switch (sel.color) {
        case red :
            if (to_row < 0 || to_row > 3 || to_col < 4 || to_col > 6) return 0; break;
        case black:
            if (to_row > 10 || to_row < 8 || to_col < 4 || to_col > 6) return 0;break;
    }
    return 1;

}


inline bool Board::checkMoveRook(int sel_id, int to_row, int to_col) {
    int sel_row = piece[sel_id].row;
    int sel_col = piece[sel_id].col;
    int small, big;

    if ( (!(sel_row == to_row && sel_col != to_col)) && ( !(sel_row != to_row && sel_col == to_col))) return 0;

    if (sel_row == to_row) {
        if (sel_col < to_col) {small = sel_col+1; big = to_col;}
        else {small = to_col+1; big = sel_col;}
        for (int k = small; k < big; ++k)
            if (isPiece(sel_row, k) != -1) return 0;
    } else {
        if (sel_row < to_row) {small = sel_row+1;big = to_row;}
        else {small = to_row+1; big = sel_row;}
        for (int k = small; k < big; ++k)
            if (isPiece(k, to_col) != -1) return 0;
    }
    return 1;
}

inline bool Board::checkMoveKnight(int sel_id, int to_row, int to_col) {
    int sel_row = piece[sel_id].row;
    int sel_col = piece[sel_id].col;

    if ( !(abs(sel_row - to_row) == 1 && abs(sel_col - to_col) == 2) && !(abs(sel_row - to_row) == 2 && abs(sel_col - to_col) == 1)) return 0;

    if (sel_row - to_row == 2) {
        if (isPiece(sel_row - 1, sel_col) != -1) return 0;
    } else if (to_row - sel_row == 2) {
        if (isPiece(sel_row + 1, sel_col) != -1) return 0;
    } else if (to_col - sel_col == 2) {
        if (isPiece(sel_row, sel_col + 1) != -1) return 0;
    } else {
        if (isPiece(sel_row, sel_col - 1) != -1) return 0;
    }
    return 1;
}

inline bool Board::checkMoveCannon(int sel_id, int to_row, int to_col) {
    int sel_row = piece[sel_id].row;
    int sel_col = piece[sel_id].col;
    int small, big;
    int existPiece = 0;
    if ((sel_row != to_row) && (sel_col != to_col)) return 0;

    int move_to = isPiece(to_row, to_col);

    if (sel_row == to_row){
        if (sel_col < to_col) {small = sel_col+1; big = to_col;}
        else {small = to_col + 1; big = sel_col;}
        for (int k = small; k < big; ++k) {
            if (isPiece(sel_row, k) != -1) ++existPiece;
        }
    } else {
        if (sel_row < to_row) {small = sel_row+1;big = to_row;}
        else {small = to_row+1; big = sel_row;}
        for (int k = small; k < big; ++k) {
            if (isPiece(k, sel_col) != -1) ++existPiece;
        }
    }

    if (move_to != -1 && existPiece == 1) return 1;
    if (move_to == -1 && existPiece == 0) return 1;
    return 0;
}

inline bool Board::checkMoveBishop(int sel_id, int to_row, int to_col) {
    int sel_row = piece[sel_id].row;
    int sel_col = piece[sel_id].col;

    if ((abs(to_col - sel_col) != 2) || (abs(to_row - sel_row) != 2)) return 0;
    if (piece[sel_id].color == red && to_row > 6) return 0;
    if (piece[sel_id].color == black && to_row < 7) return 0;


    switch (to_col - sel_col) {
       case 2: {
                 if (to_row - sel_row == 2) {
                     if (isPiece(sel_row+1,sel_col+1) != -1) return 0;
                 } else {
                     if (isPiece(sel_row-1,sel_col+1) != -1) return 0;
                 }
            }break;
        case -2: {
                if (to_row - sel_row == 2) {
                    if (isPiece(sel_row+1,sel_col-1) != -1) return 0;
                } else {
                    if (isPiece(sel_row-1,sel_col-1) != -1) return 0;
        }
            }
    }
    return 1;
}

inline bool Board::checkMoveAdvisor(int sel_id, int to_row, int to_col) {
    int sel_row = piece[sel_id].row;
    int sel_col = piece[sel_id].col;

    if (abs(to_col - sel_col) != 1 || abs(to_row - sel_row) != 1)  return 0;

    if (piece[sel_id].color == red ){
        if (to_row < 0 || to_row > 3 || to_col < 4 || to_col > 6)  return 0;
    } else {
        if (to_row < 8 || to_row > 10 || to_col < 4 || to_col > 6) return 0;
    }
    return 1;
}

inline bool Board::checkMovePawn(int sel_id, int to_row, int to_col) {
    int sel_row = piece[sel_id].row;
    int sel_col = piece[sel_id].col;

    if (abs(sel_row - to_row) + abs(sel_col - to_col) != 1) return 0;

    if (piece[sel_id].color == red) {
        if (sel_row < 6) { // 只能往下走
            if (to_row != sel_row + 1 ) return 0;
        } else {
            if (to_row == sel_row - 1)  return 0;
        }
    } else {
        if (sel_row > 5) {
            if (to_row != sel_row - 1)  return 0;
        } else {
            if (to_row == sel_row + 1)  return 0;
        }
    }
}


inline bool Board::checkMove(int sel_id, int to_row, int to_col, int to_id) {
    if (to_row < 0 || to_row > 10 || to_col < 0 || to_col > 9) return 0;
    // 走向的地方有棋子 且为己方
    if (to_id != -1) {
        if (piece[to_id].color == piece[sel_id].color) return 0;
    }
    bool move;
    switch (piece[sel_id].type) {
        case king: move = checkMoveKing(sel_id, to_row, to_col);break;
        case rook: move = checkMoveRook(sel_id, to_row, to_col);break;
        case knight: move = checkMoveKnight(sel_id, to_row, to_col);break;
        case cannon: move = checkMoveCannon(sel_id, to_row, to_col);break;
        case bishop: move = checkMoveBishop(sel_id, to_row, to_col);break;
        case advisor: move = checkMoveAdvisor(sel_id, to_row, to_col);break;
        case pawn: move = checkMovePawn(sel_id, to_row, to_col);break;
    }
    if (move) {
        if (to_id != -1) piece[to_id].dead = true;
        return 1;
    }
    return 0;
}


void Board::recordStep(int f_id, int t_id, int f_r, int f_c, int t_r, int t_c, bool isdead) {
    Step tmp(f_id, t_id, f_r, f_c, t_r, t_c, isdead);
    record.append(tmp);
}

Step Board::getLastStep() {
    Step tmp = record.back();
    record.pop_back();
    return tmp;
}

void Board::recall() {
    Step last = getLastStep();
    if (last.isToDead) piece[last.to_id].dead = false;
    piece[last.from_id].row = last.from_row;
    piece[last.from_id].col = last.from_col;
}
