#include <QtWidgets>
#include <QFont>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "custombutton.h"
#include "gamewindow.h"
#include "Appearance.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    gameWindow = new GameWindow();


    const Appearance appearance = Appearance();

    titleLabel = new QLabel;

    startGame = createButton(tr("Start New Game"), SLOT(openGameWindowClicked()), appearance);
    exitGame = createButton(tr("Exit"), SLOT(exitClicked()), appearance);

    titleLabel->setText(appearance.mainWindowTitle);
    titleLabel->setAlignment(Qt::AlignHCenter);
    titleLabel->setFont(appearance.font);
    titleLabel->minimumSizeHint();
    titleLabel->setMinimumSize(150, 100);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->addWidget(startGame, 0, 1);
    mainLayout->addWidget(exitGame, 1, 1);
    mainLayout->addWidget(titleLabel, 2, 1);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setVerticalSpacing(20);
    mainLayout->setHorizontalSpacing(40);

    QWidget* widget = new QWidget(this);
    widget->setLayout(mainLayout);
    this->setCentralWidget(widget);

    setWindowTitle(tr("The Snake (Main Menu)"));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openGameWindowClicked() {
    gameWindow->show();
}

void MainWindow::exitClicked() {
    QApplication::closeAllWindows();
}

CustomButton *MainWindow::createButton(const QString &text, const char *member, const Appearance appearance) {
    CustomButton *button = new CustomButton(text, appearance.buttonColor);
    button->setAttribute(Qt::WA_TranslucentBackground);
    button->setStyleSheet(text == "Start New Game" ? appearance.startGameStyle : appearance.exitGameStyle);
    button->setFont(appearance.font);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
