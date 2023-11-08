#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->saveButton->setVisible(false);
    ui->openButton->setVisible(QFile(fileNameString).exists());

    ui->scoreLTextLabel->setVisible(false);
    ui->scoreLNumLabel->setVisible(false);

    /*  resize(QDesktopWidget().availableGeometry().height()*1.4,
           QDesktopWidget().availableGeometry().height() - 10);
*/
    show();

    QRect rect = geometry();


    QPoint center = rect.center();
    int x = center.x() - (width()/2);
    int y = center.y() - (height()/2);
    center.setX(x);
    center.setY(y);
    move(center);

    welcomeMessageSlot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newGameSlot()
{
    gameOn = false;
    ui->saveButton->setVisible(false);

    ui->piecesWidget->resize(ui->puzzleWidget->size());

    if (ui->piecesWidget->size()!=ui->puzzleWidget->size())
    {
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning!"), tr("Widgets are different"), QMessageBox::Yes);
        msgBox.exec();
        return;
    }

    if (currentImage == QImage())
    {
        QString fileOpened = QFileDialog::getOpenFileName(this, tr("Choose your puzzle"), ".", "Images (*.png *.xpm *.bmp *.tif *.jpg)");

        if (fileOpened.isEmpty())
        {
            return;
        }

        qDebug()<<"fileopened = "<<fileOpened;

        currentImage = QImage (fileOpened);
    }

    QImage scaledImage = currentImage.scaled(ui->puzzleWidget->size(),Qt::KeepAspectRatio);

    int pieceWidth = scaledImage.width()/puzzleWidth;
    int pieceHeight = scaledImage.height()/puzzleHeight;

    leftFieldVector = QVector<QImage>();
    rightFieldVector = QVector<QImage>();

    myPuzzleVector = QVector<QImage>(puzzleWidth*puzzleHeight);

    for (int i = 0; i < puzzleHeight; i++)
    {
        for (int j = 0; j < puzzleWidth; j++)
        {
            myPuzzleVector[puzzleWidth*i + j] = scaledImage.copy(j*pieceWidth, i*pieceHeight, pieceWidth, pieceHeight);
        }
    }


    rightFieldVector = myPuzzleVector;
    leftFieldVector = QVector<QImage>(myPuzzleVector.size());
    repaintSlot();

    QMessageBox msgBox;
    msgBox.setIconPixmap(QPixmap(":/new/prefix1/icons/components.png"));
    msgBox.setWindowTitle(tr("Mess or rotate"));

    QPushButton *messButton = msgBox.addButton(tr("Mess"), QMessageBox::AcceptRole);
    QPushButton *rotateButton = msgBox.addButton(tr("Rotate"), QMessageBox::AcceptRole);
    QPushButton *resizeButton = msgBox.addButton(tr("Resize"), QMessageBox::AcceptRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==cancelButton) {
        if (QMessageBox::Yes == QMessageBox::question(this, tr("What's next?"),
                                                      tr("Start new game or exit?"),
                                                      QMessageBox::Yes|QMessageBox::Close))
        {
            currentImage = QImage();
            newGameSlot();
        }
        else
        {
            close();
        }
    }
    if (msgBox.clickedButton()==messButton) { messPuzzleSlot();   }
    if (msgBox.clickedButton()==rotateButton) {
        rotateSlot();    }
    if (msgBox.clickedButton()==resizeButton)   {   on_sizeButton_clicked(); }


    delete messButton;
    delete rotateButton;
    delete cancelButton;
    delete resizeButton;
}

void MainWindow::repaintSlot()
{
    QVector<int> wrongPiecesVector = QVector<int>();

    for (int i = 0; i < leftFieldVector.size() && i < myPuzzleVector.size(); i++)
    {
        if (leftFieldVector.at(i) != myPuzzleVector.at(i) && leftFieldVector.at(i) != QImage())
        {
            wrongPiecesVector.append(i);
        }
    }
    if (rightFieldVector.size()!=myPuzzleVector.size() && rightFieldVector!=QVector<QImage>())
    {
        gameOn = true;
        ui->saveButton->setVisible(true);
    }

    ui->puzzleWidget->repaintSlot(leftFieldVector, puzzleWidth, puzzleHeight, wrongPiecesVector);
    ui->piecesWidget->repaintSlot(rightFieldVector, puzzleWidth, puzzleHeight);

    scoreSlot(rightFieldVector.size() + wrongPiecesVector.size());

    if (leftFieldVector == myPuzzleVector && gameOn)
    {
        gameOn = false;

        ui->puzzleWidget->setSelectedInt(-1);
        ui->puzzleWidget->update();

        if (QMessageBox::Yes == QMessageBox::information(this, tr("CONGRATULATIONS!"),
                                                         tr("Done!\nDo you want to play again?"),
                                                         QMessageBox::Yes|QMessageBox::No))
        {
            currentImage = QImage();
            newGameSlot();
        }
        else
        {
            close();
        }
    }
}

void MainWindow::messPuzzleSlot()
{
    leftFieldVector = QVector<QImage>(myPuzzleVector.size());

    rightFieldVector = myPuzzleVector;
    std::random_shuffle(rightFieldVector.begin(), rightFieldVector.end());

    repaintSlot();


}

void MainWindow::pieceIsSelectedSlot(QImage image)
{
    imageSelected = image;
}

void MainWindow::placeIsSelectedSlot(int selectedPlace)
{
    if (selectedPlace == -1)
    {
        ui->piecesWidget->setSelectedInt(-1);
        imageSelected = QImage();
        return;
    }

    if (imageSelected == QImage())
    {
        return;
    }
    leftFieldVector[selectedPlace] = imageSelected;

    rightFieldVector.remove(ui->piecesWidget->getSelectedInt());
    ui->piecesWidget->setSelectedInt(-1);
    ui->piecesWidget->setSelectedPieceImage(QImage());
    repaintSlot();
    imageSelected = QImage();
}

void MainWindow::pieceToMoveSlot(int formerPlaceNumber, int currentPlaceNumber)
{
    qDebug()<<"formerPlaceNumber = "<<formerPlaceNumber<<" currentPlaceNumber = "<<currentPlaceNumber;

    if (formerPlaceNumber == -1)
    {
        return;
    }

    std::swap(leftFieldVector[currentPlaceNumber], leftFieldVector[formerPlaceNumber]);
    repaintSlot();
}

void MainWindow::pieceToDeleteSlot(int deleteNumber)
{
    qDebug()<<"pieceToDeleteSlot works";
    rightFieldVector.append(leftFieldVector.at(deleteNumber));
    leftFieldVector[deleteNumber] = QImage();

    if (leftFieldVector.size() == myPuzzleVector.size())    {
        gameOn = false;
        ui->saveButton->setVisible(false);
    }
    repaintSlot();
}

void MainWindow::pieceToRightPlaceSlot(int wrongNumber)
{
    int rightNumber = -1;
    for (int i = 0; i < myPuzzleVector.size(); i++)
    {
        if (myPuzzleVector.at(i) == leftFieldVector.at(wrongNumber))
        {
            rightNumber = i; break;
        }
    }

    if (rightNumber == wrongNumber) {   return; }

    if (leftFieldVector.at(rightNumber)!=QImage())
    {
        pieceToDeleteSlot(rightNumber);
    }
    leftFieldVector[rightNumber] = myPuzzleVector.at(rightNumber);
    leftFieldVector[wrongNumber] = QImage();

    repaintSlot();
}

void MainWindow::savePuzzleSlot()
{
    QFile file(fileNameString);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << (QVector<QImage>)myPuzzleVector;
        out << (QVector<QImage>)leftFieldVector;
        out << (QVector<QImage>)rightFieldVector;
        out << (int)puzzleWidth;
        out << (int)puzzleHeight;
        out << (QImage)currentImage;

        file.close();

        if (QFile(fileNameString).exists())
        {
            ui->openButton->setVisible(true);
        }
    }
    else {
        qDebug()<<"No file open to write";
    }
}

void MainWindow::openSavedPuzzleSlot()
{
    QFile file(fileNameString);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);    // read the data serialized from the file
        in >> myPuzzleVector >> leftFieldVector >> rightFieldVector >> puzzleWidth >> puzzleHeight >> currentImage;
        gameOn = true;
        repaintSlot();
    }
    else {
        qDebug()<<"No file open to read";
    }
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

void MainWindow::on_newGameButton_clicked()
{
    if (gameOn)
    {
        if (QMessageBox::No == QMessageBox::question(this, tr("New game"),
                                                     tr("Your current puzzle will be lost,\n"
                                                        "are you sure?"),
                                                     QMessageBox::Yes|QMessageBox::No))
        {
            return;
        }
    }

    currentImage = QImage();
    newGameSlot();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"closeEvent works";

    //    event->ignore();


    if (QMessageBox::question(this, tr("Exit"), tr("Sure?"), QMessageBox::Yes|QMessageBox::No)
        == QMessageBox::Yes)
    {
        if (gameOn)
        {
            switch (QMessageBox::question(this, tr("Save puzzle"),
                                          tr("Do you want to save your puzzle before exit?"),
                                          QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel)) {
            case QMessageBox::Save: { savePuzzleSlot(); event->accept(); break; }
            case QMessageBox::Discard: { event->accept(); break; }
            case QMessageBox::Cancel: { return; /*break;*/ }
            default:
                break;
            }
        }
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && gameOn)
    {
        ui->puzzleWidget->repaintSlot(myPuzzleVector, puzzleWidth, puzzleHeight, QVector<int>());
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && gameOn)
    {
        QVector<int> wrongPiecesVector = QVector<int>();

        for (int i = 0; i < leftFieldVector.size() && i < myPuzzleVector.size(); i++)
        {
            if (leftFieldVector.at(i) != myPuzzleVector.at(i) && leftFieldVector.at(i) != QImage())
            {
                wrongPiecesVector.append(i);
            }
        }

        ui->puzzleWidget->repaintSlot(leftFieldVector, puzzleWidth, puzzleHeight, wrongPiecesVector);
    }
}

void MainWindow::on_sizeButton_clicked()
{
    if (gameOn)
    {
        if (QMessageBox::No == QMessageBox::information(this, tr("Resize"),
                                                        tr("Do you want to change the size?"),
                                                        QMessageBox::Yes|QMessageBox::No))
        {
            return;
        }
    }

    QMessageBox msgBox;

    msgBox.setWindowTitle(tr("Size"));
    msgBox.setText(tr("Choose size of a puzzle:"));
    msgBox.setIconPixmap(QPixmap(":/new/prefix1/icons/components.png"));

    QPushButton *easyButton = msgBox.addButton(tr("50 pieces"), QMessageBox::AcceptRole);
    QPushButton *averageButton = msgBox.addButton(tr("300 pieces"), QMessageBox::AcceptRole);
    QPushButton *hardButton = msgBox.addButton(tr("1000 pieces"), QMessageBox::AcceptRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==cancelButton) { return; }
    if (msgBox.clickedButton()==easyButton) { puzzleWidth = 5; puzzleHeight = 10;   }
    if (msgBox.clickedButton()==averageButton) { puzzleWidth = 15; puzzleHeight = 20;    }
    if (msgBox.clickedButton()==hardButton) { puzzleWidth = 25; puzzleHeight = 40;   }

    delete easyButton;
    delete averageButton;
    delete hardButton;
    delete cancelButton;

    if (gameOn)
    {
        gameOn = false;
        newGameSlot();
    }
    else
    {
        newGameSlot();
    }
}

void MainWindow::on_saveButton_clicked()
{
    if (QFile(fileNameString).exists())
    {
        if (QMessageBox::No == QMessageBox::question(this, tr("Rewrite"),
                                                     tr("You've already have a saved puzzle,\n"
                                                        "do you want to rewrite it?"),
                                                     QMessageBox::Yes|QMessageBox::No))
        {
            return;
        }
    }

    savePuzzleSlot();
}

void MainWindow::on_openButton_clicked()
{
    if (gameOn)
    {
        if (QMessageBox::No == QMessageBox::question(this, tr("Open puzzle"),
                                                     tr("Your current puzzle will be lost,\n"
                                                        "are you sure?"),
                                                     QMessageBox::Yes|QMessageBox::No))
        {
            return;
        }
    }

    openSavedPuzzleSlot();
}

void MainWindow::rotateSlot()
{
    if (gameOn) {   return; }
    if (currentImage == QImage())   {   return; }

    QImage  rotatedImage = QImage(currentImage.height(), currentImage.width(), currentImage.format());
    for (int i = 0; i < rotatedImage.width() && i < currentImage.height(); i++)
    {
        for (int j = 0; j < rotatedImage.height() && j < currentImage.width(); j++)
        {
            rotatedImage.setPixel(i, j, currentImage.pixel(j, currentImage.height()- i - 1));
        }
    }
    currentImage = rotatedImage;
    newGameSlot();
}

void MainWindow::welcomeMessageSlot()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle(tr("Welcome!"));
    msgBox.setIconPixmap(QPixmap(":/new/prefix1/icons/components.png"));

    QPushButton *startButton = msgBox.addButton(tr("New Game"), QMessageBox::AcceptRole);
    QPushButton *openRulesButton = nullptr;
    if (  QFile(fileNameString).exists())    {
        openRulesButton = msgBox.addButton(tr("Open"), QMessageBox::AcceptRole);
        msgBox.setText(tr("Welcome to our game!\nYou can start new game or open your saved puzzle"));
    }
    else {
        openRulesButton = msgBox.addButton(tr("Rules"), QMessageBox::AcceptRole);
        msgBox.setText(tr("Welcome to our game!\nYou can start new game or read rules first"));
    }
    msgBox.exec();

    if (msgBox.clickedButton()==startButton)    {
        newGameSlot();
    }
    else  {
        if (QFile(fileNameString).exists()) {
            openSavedPuzzleSlot();
        }

        else    {
            rulesShowSlot();
        }
    }
    delete startButton;
    delete openRulesButton;
}

void MainWindow::rulesShowSlot()
{
    QMessageBox msgBox;
    //    msgBox.setIconPixmap(QPixmap(":/new/prefix1/icons/components.png"));

    QString rulesStr(tr("You need to assemble a puzzle on the left side of the field\n"
                        "You can set for a puzzle any picture you want\n"
                        "To choose a piece - click the left mouse button\n"
                        "To replace a piece - drug it with the mouse\n"
                        "To remove a piece from the field - click the right mouse button\n"
                        "Pieces on wrong places are in red frames\n"
                        "To set a piece on correct place -\n"
                        "click the right mouse button with Ctrl-key pressed\n"
                        "Good luck!"));

    msgBox.setWindowTitle(tr("Rules and control"));
    msgBox.setText(rulesStr);

    QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::AcceptRole);
    msgBox.exec();
    if (msgBox.clickedButton()==okButton) {   return;   }
}

void MainWindow::on_rulesButton_clicked()
{
    rulesShowSlot();
}

void MainWindow::scoreSlot(int detailsLeft)
{
    if (detailsLeft > 0) {
        ui->scoreLNumLabel->setVisible(true);
        ui->scoreLTextLabel->setVisible(true);
        ui->scoreLNumLabel->setNum(detailsLeft);
    }
    else {
        ui->scoreLNumLabel->setVisible(false);
        ui->scoreLTextLabel->setVisible(false);
    }
}


void MainWindow::on_aboutButton_clicked()
{
    QMessageBox msgBox;

    QString aboutsStr(tr("This application was developed by Igor Medvedev in 2019\n"
                         "You can play it for free, share it with your friends or use it for any other non-commercial purposes"));

    msgBox.setWindowTitle(tr("About the application"));
    msgBox.setText(aboutsStr);

    QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::AcceptRole);
    msgBox.exec();
    if (msgBox.clickedButton()==okButton) {   return;   }
}
