#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <QtWidgets>
#include <QFont>

struct Appearance {
    QColor const buttonColor = QColor(155, 175, 195);
    QString const mainWindowTitle = "Hello! It's a snake game.\nHope you enjoy it!";
    QString const gameOverTitle = "Game over.\nWhiteSpace - start new game\nEscape - exit game.";
    QString const scoreTitle = "Score: ";
    QString const startGameStyle =
                            "background-color: green;"
                            "border: 1px white;"
                            "border-radius: 15px;"
                            "color: lightGray; ";

    QString const exitGameStyle =
                            "background-color: darkRed;"
                            "border: 1px white;"
                            "border-radius: 15px;"
                            "color: lightGray;";

    QFont const font = QFont("Courier", 15, QFont::DemiBold);
};

#endif // APPEARANCE_H
