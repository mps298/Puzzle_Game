
#include "puzzleview.h"


int PuzzleView::getSelectedInt() const
{
    return selectedInt;
}

void PuzzleView::setSelectedInt(int value)
{
    selectedInt = value;
}

QVector<int> PuzzleView::getWrongPiecesVector() const
{
    return wrongPiecesVector;
}

void PuzzleView::setWrongPiecesVector(const QVector<int> &value)
{
    wrongPiecesVector = value;
}

PuzzleView::PuzzleView(QWidget *parent) : QWidget(parent)
{

}

QVector<QImage> PuzzleView::getCurrentPuzzleVector() const
{
    return currentPuzzleVector;
}

void PuzzleView::setCurrentPuzzleVector(const QVector<QImage> &value)
{
    currentPuzzleVector = value;
}

int PuzzleView::getCurrentWidth() const
{
    return currentWidth;
}

void PuzzleView::setCurrentWidth(int value)
{
    currentWidth = value;
}

int PuzzleView::getCurrentHeight() const
{
    return currentHeight;
}

void PuzzleView::setCurrentHeight(int value)
{
    currentHeight = value;
}

void PuzzleView::newGameSlot()
{
    //    qDebug()<<"newGameSlot of PuzzleView works";
}

void PuzzleView::repaintSlot(const QVector<QImage> &myVector, int myWidth, int myHeight, const QVector<int> &wrongVector)
{
    //    qDebug()<<"repaintSlot of PuzzleView works";

    setCurrentPuzzleVector(myVector);
    setCurrentWidth(myWidth);
    setCurrentHeight(myHeight);
    setWrongPiecesVector(wrongVector);

    update();
}

void PuzzleView::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"w = "<<width()<<", h = "<<height();

    if (currentWidth < 0 || currentHeight < 0)
    {
        return;
    }

    int w = width()/currentWidth;
    int h = height()/currentHeight;
    int currentX = event->pos().x() / w;
    int currentY = event->pos().y() / h;

    selectedInt = currentY*currentWidth + currentX;

    if (selectedInt < 0 || selectedInt >= currentPuzzleVector.size())
    {
        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        if (currentPuzzleVector.at(selectedInt)!=QImage())
        {
            isCaptured = true;
            capturedPoint = QPoint(currentX*w, currentY*h);
            capturedCursorPoint = event->pos();
            capturedImage = currentPuzzleVector.at(selectedInt);
            emit placeIsSelectedSignal(-1);
            return;
        }
        emit placeIsSelectedSignal(selectedInt);
    }
    else if (event->button() == Qt::RightButton)
    {
        if (event->modifiers()==Qt::CTRL)
        {
            emit pieceToRightPlaceSignal(selectedInt);
        }
        else {
            if (currentPuzzleVector.at(selectedInt) != QImage())    {
                qDebug()<<"Right burron, selectedInt = "<<selectedInt;
                emit pieceToDeleteSignal(selectedInt);
            }
        }
    }
    selectedInt = -1;
}

void PuzzleView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(QBrush(Qt::darkGray), 1));

    int w = width()/currentWidth;
    int h = height()/currentHeight;

    for (int i = 0; i < currentPuzzleVector.size(); i++)
    {
        QRect rect = QRect(QPoint((i%currentWidth)*w, i/currentWidth*h), QSize(w, h));

        painter.drawRect(rect);
        if (currentPuzzleVector.at(i) != capturedImage)
        {
            painter.drawImage(rect, currentPuzzleVector.at(i));
        }

        if (i == selectedInt)
        {
            painter.fillRect(rect, QColor(255, 255, 255, 100));
        }
    }

    if (!wrongPiecesVector.isEmpty())
    {
        painter.setPen(QPen(QBrush(Qt::red), 5));
        for (int i = 0; i < wrongPiecesVector.size(); i++)
        {
            if (currentPuzzleVector.at(wrongPiecesVector.at(i)) != capturedImage)
            {
                painter.drawRect(QRect(QPoint((wrongPiecesVector.at(i)%currentWidth)*w, wrongPiecesVector.at(i)/currentWidth*h), QSize(w, h)));
            }
        }
    }


    if (capturedImage!=QImage() && isCaptured)
    {
        painter.drawImage(QRect(capturedPoint, QSize(w, h)), capturedImage);

        for (auto element: wrongPiecesVector)
        {
            if (currentPuzzleVector.at(element) == capturedImage)
            {
                painter.drawRect(QRect(capturedPoint, QSize(w, h)));
                break;
            }
        }
    }

    painter.setPen(QPen(QBrush(Qt::darkBlue), 3));
    painter.drawRect(QRect(0,0,width(),height()));
}

void PuzzleView::mouseReleaseEvent(QMouseEvent *event)
{
    int w = width()/currentWidth;
    int h = height()/currentHeight;

    int currentX = event->pos().x() / /*%*/ w;
    if (currentX < 0) { currentX = 0;    }
    if (currentX > currentWidth - 1) {  currentX = currentWidth - 1;    }

    int currentY = event->pos().y() / /*%*/ h;
    if (currentY < 0) { currentY = 0;    }
    if (currentY > currentHeight - 1) {  currentY = currentHeight - 1;    }

    int currentInt = currentY*currentWidth + currentX;
    qDebug()<<"currInt = "<<currentInt;

    capturedCursorPoint = QPoint();
    capturedImage = QImage();
    capturedPoint = QPoint();

    if (isCaptured)
    {
        emit  pieceToMoveSignal(selectedInt, currentInt);
        isCaptured = false;
    }

    selectedInt = -1;
}

void PuzzleView::mouseMoveEvent(QMouseEvent *event)
{
    if (capturedImage == QImage())
    {
        return;
    }
    else
    {
        int currentX = event->x() - capturedCursorPoint.x();
        int currentY = event->y() - capturedCursorPoint.y();

        capturedPoint.setX(capturedPoint.x() + currentX);
        capturedPoint.setY(capturedPoint.y() + currentY);

        if (capturedPoint.x() <= 0 && currentX < 0) {
            capturedPoint.setX(0); }
        if (capturedPoint.x() >= width() - (width()/currentWidth) - 1 && currentX > 0) {
            capturedPoint.setX(width() - (width()/currentWidth) - 1); }
        if (capturedPoint.y() <= 0 && currentY < 0) {
            capturedPoint.setY(0); }
        if (capturedPoint.y() >= height() - (height()/currentHeight) - 1 && currentY > 0) {
            capturedPoint.setY(height() - (height()/currentHeight) - 1); }

        if (capturedPoint.x() <= 0 && currentX < 0) {
            capturedPoint.setX(0); }
        if (capturedPoint.x() >= width() - (width()/currentWidth) - 1 && currentX > 0) {
            capturedPoint.setX(width() - (width()/currentWidth) - 1); }
        if (capturedPoint.y() <= 0 && currentY < 0) {
            capturedPoint.setY(0); }
        if (capturedPoint.y() >= height() - (height()/currentHeight) - 1 && currentY > 0) {
            capturedPoint.setY(height() - (height()/currentHeight) - 1); }

        qDebug()<<"currX = "<<currentX<<", currY = "<<currentY;

        qDebug()<<"captX = "<<capturedPoint.x()<<"captY = "<<capturedPoint.y();

        if (capturedCursorPoint.x() + currentX > 0 && capturedCursorPoint.x() + currentX < width())
        {
            capturedCursorPoint.setX(capturedCursorPoint.x() + currentX);
        }

        if (capturedCursorPoint.y() + currentY > 0 && capturedCursorPoint.y() + currentY < height())
        {
            capturedCursorPoint.setY(capturedCursorPoint.y() + currentY);
        }

        qDebug()<<"captCursorX = "<<capturedCursorPoint.x()<<"captCursorY = "<<capturedCursorPoint.y();


        update();
    }
}
