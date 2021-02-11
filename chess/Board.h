#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Piece.h"
#include "Step.h"
#include <QVector>
#include <QButtonGroup>


#ifndef dist
#define dist 60
#endif

#ifndef r_chess
#define r_chess (dist / 2.5)
#endif

#ifndef fineLinelength
#define fineLinelength (dist / 4)
#endif

#ifndef space
#define space (dist / 12)
#endif

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    Color mycolor;

    Piece piece[32];

    int selected;
    bool rotate;

    QVector<Step> record;

    QPoint moveto;

    void setPiece(int id, int row, int col, bool dead, Color c, Type type);
    void drawPiece(QPainter* p, int id);
    void drawFineLine(QPainter *p,int i, int j);

    virtual void paintEvent(QPaintEvent * event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    inline int isPiece(int row, int col);
    inline int isMyPiece(int row, int col);


    inline bool checkMove(int sel_id, int to_row, int to_col, int to_id);
    inline bool checkMoveKing(int sel_id, int to_row, int to_col);
    inline bool checkMoveRook(int sel_id, int to_row, int to_col);
    inline bool checkMoveKnight(int sel_id, int to_row, int to_col);
    inline bool checkMoveCannon(int sel_id, int to_row, int to_col);
    inline bool checkMoveBishop(int sel_id, int to_row, int to_col);
    inline bool checkMoveAdvisor(int sel_id, int to_row, int to_col);
    inline bool checkMovePawn(int sel_id, int to_row, int to_col);

    void recordStep(int f_id, int t_id, int f_r, int f_c, int t_r, int t_c, bool isdead);
    Step getLastStep();
    void recall();


signals:

public slots:

};

#endif // BOARD_H
