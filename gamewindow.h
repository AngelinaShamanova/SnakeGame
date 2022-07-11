#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include "custombutton.h"
#include "Appearance.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
private slots:
    void backToMainClicked();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
private:
    Ui::GameWindow *ui;

    QImage dot;
    QImage head;
    QImage apple;

    static const int gameFieldWidth = 300;
    static const int gameFieldHeight = 300;
    static const int bodyElementSize = 10;
    static const int allPositions = 900;
    static const int randomApplePosition = 29;
    static const int delay = 140;

    int timerId;
    int dots;
    int apple_x;
    int apple_y;

    int temporaryScore;

    int x[allPositions];
    int y[allPositions];

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;
    bool gameIsOver;

    void loadImages();
    void startGame();
    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void drawing();
    void gameOver(QPainter &);
};

#endif // GAMEWINDOW_H
