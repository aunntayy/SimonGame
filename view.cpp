/**
* @authors Chanphone Visathip and Phuc Hoang
* @authors Githubs: aunntayy and PhucHoang123
*
* @date 10/24/2024
* @title A6 Qt Simon Game
*
* @brief The view class is responsible for rendering the game's visual elements
* and managing interactions between the player and the game UI for the Simon game.
* It provides functions to update button states, display animations, and respond
* to player actions.
*/
#include "view.h"
#include "ui_view.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QRandomGenerator>
#include <QTimer>
#include <QColorDialog>

MainWindow::MainWindow(class gameModel *model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gameModel(model) {
    ui->setupUi(this);
    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "   border: 2px solid grey;"
        "   border-radius: 5px;"
        "   background-color: #FFFFFF;"
        "   text-align: center;"
        "   font-size: 30px;"
        "   color: black;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: #00FF00;"
        "   width: 20px;"
        "}");

    ui->redButton->setStyleSheet(
        "QPushButton { background-color: rgb(150, 40, 40); border: 1px solid transparent;}");

    ui->blueButton->setStyleSheet(
        "QPushButton { background-color: rgb(40, 75, 125); border: 1px solid transparent;}");
    ui->progressBar->setValue(0);
    // Connection for User input
    connect(ui->startButton, &QPushButton::clicked, this,
            &MainWindow::startButtonClicked);
    connect(ui->playAgainButton, &QPushButton::clicked, this,
            &MainWindow::startButtonClicked);
    connect(ui->blueButton, &QPushButton::clicked, this,
            &MainWindow::blueButtonClicked);
    connect(ui->redButton, &QPushButton::clicked, this,
            &MainWindow::redButtonClicked);

    connect(ui->pushButton, &QPushButton::clicked,this,
            &MainWindow::colorPicker);

    // Connection between model and view
    connect(gameModel, &gameModel::red, this, &MainWindow::popUpRed);
    connect(gameModel, &gameModel::blue, this, &MainWindow::popUpBlue);
    connect(gameModel, &gameModel::gameProgress, this, &MainWindow::updateProgressBar);
    connect(gameModel, &gameModel::gameOver, this, &MainWindow::gameOverPopUp);
    connect(gameModel, &gameModel::disableButton, this, &MainWindow::toggleButton);
    connect(gameModel, &gameModel::onLevelComplete, this, &MainWindow::showConfetti);

    // Initial set up for UI
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);

    ui->playAgainButton->setVisible(false);
    ui->playOverMessage->setVisible(false);
}

MainWindow::~MainWindow() {
    delete ui;
    delete gameModel;
}

void MainWindow::colorPicker(){
    colorpicker.setVisible(true);
}
void MainWindow::startButtonClicked() {
    gameModel->startGame();
    ui->startButton->setVisible(false);
    ui->playAgainButton->setVisible(false);
    ui->playOverMessage->setVisible(false);
}

void MainWindow::popUpRed() {
    ui->redButton->setStyleSheet(
        QString("QPushButton{background-color: rgb(255, 80, 80)}"));
    QTimer::singleShot(300, this, [this]() {
        ui->redButton->setStyleSheet(
            QString("QPushButton{background-color: rgb(150, 40, 40)}"));
    });
}

void MainWindow::popUpBlue() {
    ui->blueButton->setStyleSheet(
        QString("QPushButton{background-color: rgb(80, 150, 255)}"));
    QTimer::singleShot(300, this, [this]() {
    ui->blueButton->setStyleSheet(
        QString("QPushButton{background-color: rgb(40, 75, 125)}"));
    });
}

void MainWindow::blueButtonClicked() {
    gameModel->checkForCorrect(gameModel::Color::Blue);
}

void MainWindow::redButtonClicked() {
    // same with blue
    gameModel->checkForCorrect(gameModel::Color::Red);
}

void MainWindow::updateProgressBar(int value) {
    ui->progressBar->setValue(value);
}

void MainWindow::gameOverPopUp() {
    ui->playAgainButton->setVisible(true);
    ui->playOverMessage->setVisible(true);
    ui->startButton->setVisible(false);
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
}

void MainWindow::toggleButton(bool enable){
    ui->redButton->setEnabled(enable);
    ui->blueButton->setEnabled(enable);
}

void MainWindow::showConfetti() {
    // Check if scene already exist to avoid create multiple instances
    if (!ui->graphicsView->scene()) {
        QGraphicsScene* scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
    }

    for (int i = 0; i < 30; i++) {
        // Create a small confetti circle
        QGraphicsRectItem *confetti = new QGraphicsRectItem(0, 0, 10, 30);
        confetti->setRotation(QRandomGenerator::global()->bounded(360));
        // Random color for each confetti piece
        QColor color = QColor::fromRgb(
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256)
            );
        confetti->setBrush(color);

        // Add confetti to scene at a random x-position at the top
        int startX = QRandomGenerator::global()->bounded(ui->graphicsView->width());
        confetti->setPos(startX, 0);
        ui->graphicsView->scene()->addItem(confetti);

        // Create a QTimeLine and QGraphicsItemAnimation to animate the confetti
        QTimeLine* timeline = new QTimeLine(500 + QRandomGenerator::global()->bounded(500), this);
        timeline->setFrameRange(0, 100);

        QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
        animation->setItem(confetti);
        animation->setTimeLine(timeline);

        // Set the animation path (from top to bottom)
        animation->setPosAt(1.0, QPointF(startX, ui->graphicsView->height()));

        // Start the timeline
        timeline->start();

        // Clean up the confetti item after the animation completes
        connect(timeline, &QTimeLine::finished, [timeline, animation, confetti]() {
            delete timeline;
            delete animation;
            delete confetti;
        });
        timeline->start();
    }
    // Remove the scene after 2 seconds to reset
    QTimer::singleShot(2000, ui->graphicsView->scene(), [this]() {
        ui->graphicsView->scene()->clear();
    });
}

