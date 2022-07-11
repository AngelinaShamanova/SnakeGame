#include <QPainter>
#include <QTime>
#include <QGraphicsTextItem>
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "Appearance.h"
#include "custombutton.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow) {
    ui->setupUi(this);

    setStyleSheet("background-color:black;");

    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;
    gameIsOver = false;

    resize(gameFieldWidth, gameFieldHeight);
    loadImages();
    startGame();

    setWindowTitle(tr("The Snake"));
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::backToMainClicked() {
    this->close();
}

void GameWindow::loadImages() {
    dot.load(":/dot.png");
    head.load(":/head.png");
    apple.load(":/apple.png");
}

void GameWindow::startGame() {
    gameIsOver = false;
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    temporaryScore = 0;

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateApple();

    timerId = startTimer(delay);
}

void GameWindow::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    drawing();
}

void GameWindow::drawing() {
    QPainter qp(this);

    if (inGame) {
        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }
        temporaryScore += 1;
    } else {
        gameOver(qp);
    }
}

void GameWindow::gameOver(QPainter &qp) {
    const Appearance appearance = Appearance();

    QString highScoreTitle = QString::number(temporaryScore);

    QString message = appearance.gameOverTitle + "\n\n" + appearance.scoreTitle + highScoreTitle + "\n";

    gameIsOver = true;

    QRect clip(0, 0, width(), height());

    qp.setPen(QColor(Qt::white));
    qp.setFont(appearance.font);
    qp.drawText(clip, Qt::AlignCenter | Qt::RichText | Qt::TextIncludeTrailingSpaces, message);
}

void GameWindow::checkApple() {
    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        dots++;
        locateApple();
    }
}

void GameWindow::move() {
    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= bodyElementSize;
    }

    if (rightDirection) {
        x[0] += bodyElementSize;
    }

    if (upDirection) {
        y[0] -= bodyElementSize;
    }

    if (downDirection) {
        y[0] += bodyElementSize;
    }
}

void GameWindow::checkCollision() {
    for (int z = dots; z > 0; z--) {
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= gameFieldHeight) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= gameFieldWidth) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if (!inGame) {
        killTimer(timerId);
    }
}

void GameWindow::locateApple() {
    QTime time = QTime::currentTime();
    srand((uint) time.msec());

    int r = rand() % randomApplePosition;
    apple_x = (r * bodyElementSize);

    r = rand() % randomApplePosition;
    apple_y = (r * bodyElementSize);
}

void GameWindow::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    if (inGame) {
        checkApple();
        checkCollision();
        move();
    }

    repaint();
}

void GameWindow::keyPressEvent(QKeyEvent *e) {
    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if (key == Qt::Key_Escape) {
        backToMainClicked();
    }

    if ((key == Qt::Key_Space) && (gameIsOver)) {
        startGame();
    }

    QWidget::keyPressEvent(e);
}
