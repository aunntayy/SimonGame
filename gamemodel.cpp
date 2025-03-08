/**
 * @authors Chanphone Visathip and Phuc Hoang
 * @authors Githubs: aunntayy and PhucHoang123
 *
 * @date 10/24/2024
 * @title A6 Qt Simon Game
 *
 * @brief The gameModel class manages the game's logic and sequence generation
 * for the Qt-based Simon game. It includes functions for starting the game,
 * generating sequences, handling color signals, and controlling game flow.
 */
#include "gameModel.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
gameModel::gameModel(QObject *parent) : QObject(parent) {}

// Start game
void gameModel::startGame() {
    level = 1;
    currentIndex = 0;
    currentSequence.clear();
    generateNewLevel();
    showNewLevel();
}

// Generate new level and keep adding on with the prvious
void gameModel::generateNewLevel() {
    gameModel::Color newColorSeq = randomColorGenerator();
    currentSequence.append(newColorSeq);
}

// Generate color blue and red
gameModel::Color gameModel::randomColorGenerator() {
    int randomNum = QRandomGenerator::global()->bounded(0, 2);
    return (randomNum == 1) ? gameModel::Color::Red : gameModel::Color::Blue;
}

// Check for red or blue and signal mainwindow
void gameModel::checkRedorBlue(Color color) {
    if (color == gameModel::Color::Red) {
        emit red();
    } else {
        emit blue();
    }
}

// Show sequence to the main view window
void gameModel::showNewLevel() {
    QTimer::singleShot(200, this, [this]() { emit gameProgress(0); });
    emit disableButton(false);
    int baseDelay = calculateGameSpeed();
    int cumulativeDelay = 200;
    for (int i = 0; i < currentSequence.size(); i++) {
        gameModel::Color currentColor = currentSequence[i];
        QTimer::singleShot(cumulativeDelay, this, [this, currentColor]() {
            checkRedorBlue(currentColor);
        });
    cumulativeDelay += baseDelay;
    }
    QTimer::singleShot(cumulativeDelay, this,
                       [this]() { emit disableButton(true); });
}

// Check for correct
void gameModel::checkForCorrect(Color color) {
    if (color == currentSequence[currentIndex]) {
        currentIndex++;
        int progressValue = (currentIndex * 100) / currentSequence.size();
        emit gameProgress(progressValue);
        if (currentIndex == currentSequence.size()) {
            level++;
            generateNewLevel();
            emit onLevelComplete();
            currentIndex = 0;
            showNewLevel();
        }
    } else {
        level = 1;
        qDebug() << level;
        emit gameOver();
    }
}

int gameModel::calculateGameSpeed() {
    int delay = initialDelay - (level * speedUp);
    return (delay > minDelay) ? delay : minDelay;
}
