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
#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "gameModel.h"
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow, initializing the UI and game model.
     * @param gameModel Pointer to the game's logic model.
     * @param parent Optional parent widget for the main window, default is nullptr.
     */
    MainWindow(gameModel* gameModel, QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow, freeing allocated resources.
     */
    ~MainWindow();

public slots:
    /**
     * @brief Slot to handle the start button click event,
     * initializing the game and enabling color buttons.
     */
    void startButtonClicked();

    /**
     * @brief Slot to handle the display of the Red button
     * when the sequence requires it.
     */
    void popUpRed();

    /**
     * @brief Slot to handle the display of the Blue button
     * when the sequence requires it.
     */
    void popUpBlue();

    /**
     * @brief Displays a game-over popup when the player makes an incorrect move.
     */
    void gameOverPopUp();

    /**
     * @brief Slot to handle the player clicking the Blue button.
     * Processes the player's input for game logic.
     */
    void blueButtonClicked();

    /**
     * @brief Slot to handle the player clicking the Red button.
     * Processes the player's input for game logic.
     */
    void redButtonClicked();

    /**
     * @brief Updates the progress bar based on the game's current progress.
     * @param value Current progress value to display in the progress bar.
     */
    void updateProgressBar(int value);

    /**
     * @brief Enables or disables the color buttons based on the game state.
     * @param enable Boolean indicating whether buttons should be enabled (true) or disabled (false).
     */
    void toggleButton(bool enable);

    /**
     * @brief Displays a confetti animation on the screen to celebrate level completion.
     */
    void showConfetti();


    void colorPicker();
private:
    Ui::MainWindow *ui;
    gameModel *gameModel;
    QColorDialog colorpicker;
    QPalette palette;
};
#endif // VIEW_H
