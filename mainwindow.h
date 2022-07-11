#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "gamewindow.h"
#include "Appearance.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomButton;
class QLineEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    int score = 0;

    Ui::MainWindow *ui;
    GameWindow *gameWindow;

    QLineEdit *display;

    QLabel *titleLabel;

    CustomButton *startGame;
    CustomButton *exitGame;
    CustomButton *createButton (const QString &text, const char *member, const Appearance appearance);

private slots:
    void openGameWindowClicked();
    void exitClicked();
};
#endif // MAINWINDOW_H
