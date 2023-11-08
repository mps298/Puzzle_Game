#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QVector>
#include <QDataStream>
#include <QScreen>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVector<QImage> myPuzzleVector = QVector<QImage>();
    QVector<QImage> leftFieldVector = QVector<QImage>();
    QVector<QImage> rightFieldVector = QVector<QImage>();

    const QString fileNameString = "puzzle_saved.data";


    QImage currentImage = QImage();
    QImage imageSelected = QImage();

    int puzzleWidth = 5;
    int puzzleHeight = 10;

    bool gameOn = false;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newGameSlot();
    void repaintSlot();
    void messPuzzleSlot();

    void pieceIsSelectedSlot(QImage image);
    void placeIsSelectedSlot(int selectedPlace);
    void pieceToMoveSlot(int formerPlaceNumber, int currentPlaceNumber);
    void pieceToDeleteSlot(int deleteNumber);
    void pieceToRightPlaceSlot (int wrongNumber);

    void savePuzzleSlot();
    void openSavedPuzzleSlot();

    void on_closeButton_clicked();
    void on_newGameButton_clicked();   
    void on_sizeButton_clicked();
    void on_saveButton_clicked();
    void on_rulesButton_clicked();
    void on_openButton_clicked();
    void on_aboutButton_clicked();

    void rotateSlot();
    void welcomeMessageSlot();
    void rulesShowSlot();
    void scoreSlot(int detailsLeft = 0);



private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
