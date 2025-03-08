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
#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QColor>
#include <QObject>
#include <QVector>

class gameModel : public QObject {
    Q_OBJECT

public:
    /**
     * @brief gameModel constructor
     * @param Optional parent of type QObject, default is nullptr
     */
    explicit gameModel(QObject *parent = nullptr);

    /**
     * @brief enumerator class to represent type color Red and Blue
     */
    enum Color { Red, Blue };

    /**
     * @brief calculate game speed
     */
    int calculateGameSpeed();

public slots:

    /**
     * @brief Initializes the game and starts the first sequence
     */
    void startGame();

    /**
     * @brief Generates a new level by adding a color to the sequence
     */
    void generateNewLevel();

    /**
     * @brief Checks if the given color matches the expected color in the sequence
     * @param color The color to check against the current sequence
     */
    void checkRedorBlue(Color color);

    /**
     * @brief Randomly generates either a Red or Blue color
     * @return The randomly generated color
     */
    Color randomColorGenerator();

    /**
     * @brief Displays the sequence to the player
     */
    void showNewLevel();

    /**
     * @brief Checks if the player’s input matches the expected sequence color
     * @param color The color input by the player
     */
    void checkForCorrect(Color color);

signals:
    /**
     * @brief Emitted when the color Red needs to be displayed
     * in the Simon game sequence.
     */
    void red();

    /**
     * @brief Emitted when the color Blue needs to be displayed
     * in the Simon game sequence.
     */
    void blue();

    /**
     * @brief Emitted to update the game's progress bar or status.
     * @param value Integer representing the current progress value.
     */
    void gameProgress(int value);

    /**
     * @brief Emitted when the player makes a mistake, ending the game.
     * Triggers game-over logic in the main UI.
     */
    void gameOver();

    /**
     * @brief Emitted to enable or disable the game buttons.
     * @param buttonStatus Boolean indicating if buttons should be enabled (true) or disabled (false).
     */
    void disableButton(bool buttonStatus);

    /**
     * @brief Emitted when the player successfully completes a level.
     * Signals the main UI to handle level completion events.
     */
    void onLevelComplete();

private:
    QVector<Color> currentSequence;
    int currentIndex;
    int level;
    int minDelay = 500;
    int speedUp = 100;
    int initialDelay = 1500;
};

#endif // GAMEMODEL_H
