#include "piecesview.h"

QImage PiecesView::getSelectedPieceImage() const
{
    return selectedPieceImage;
}

void PiecesView::setSelectedPieceImage(const QImage &value)
{
    selectedPieceImage = value;
}

int PiecesView::getSelectedInt() const
{
    return selectedInt;
}

void PiecesView::setSelectedInt(int value)
{
    selectedInt = value;
}

PiecesView::PiecesView(QWidget *parent) : QWidget(parent)
{

}

QVector<QImage> PiecesView::getCurrentPuzzleVector() const
{
    return currentPieceVector;
}

void PiecesView::setCurrentPuzzleVector(const QVector<QImage> &value)
{
    currentPieceVector = value;
}

int PiecesView::getCurrentWidth() const
{
    return currentWidth;
}

void PiecesView::setCurrentWidth(int value)
{
    currentWidth = value;
}

int PiecesView::getCurrentHeight() const
{
    return currentHeight;
}

void PiecesView::setCurrentHeight(int value)
{
    currentHeight = value;
}

void PiecesView::newGameSlot()
{

}

void PiecesView::repaintSlot(const QVector<QImage> &myVector, int myWidth, int myHeight)
{
    setCurrentPuzzleVector(myVector);
    setCurrentWidth(myWidth);
    setCurrentHeight(myHeight);

    update();
}

void PiecesView::mousePressEvent(QMouseEvent *event)
{
    if (currentPieceVector == QVector<QImage>())
    {
//        qDebug()<<"pieceView is empty";
        return;
    }

    if (event->button() == Qt::RightButton)
    {
        selectedPieceImage = QImage();
        selectedInt = -1;

        emit pieceIsSelectedSignal(selectedPieceImage);
//        update();
    }

    else if (event->button() == Qt::LeftButton)
    {
        int w = width()/currentWidth;
        int h = height()/currentHeight;

        int currentX = event->pos().x() / w;
        int currentY = event->pos().y() / h;

        qDebug()<<"x = "<<currentX<<", y = "<<currentY;

        selectedInt = currentY*currentWidth + currentX;

        if (selectedInt >= currentPieceVector.size() || currentPieceVector.at(selectedInt) == QImage())
        {
            selectedInt = -1;
            return;
        }
        emit pieceIsSelectedSignal(currentPieceVector.at(selectedInt));
            update();
    }
}

void PiecesView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(QBrush(Qt::darkGray), 1));

    int w = width()/currentWidth;
    int h = height()/currentHeight;

    for (int i = 0; i < currentPieceVector.size(); i++)
    {
        QRect rect = QRect(QPoint((i%currentWidth)*w, i/currentWidth*h), QSize(w, h));
        painter.drawImage(rect, currentPieceVector.at(i));
        painter.drawRect(rect);

        if (i == selectedInt)
        {
            painter.fillRect(rect, QColor(255, 255, 255, 100));
        }
    }

    painter.setPen(QPen(QBrush(Qt::darkBlue), 3));
    painter.drawRect(QRect(0,0,width(),height()));
}
