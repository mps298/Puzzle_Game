#ifndef PUZZLEVIEW_H
#define PUZZLEVIEW_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QImage>
#include <QDebug>
#include <QMouseEvent>

class PuzzleView : public QWidget
{
    Q_OBJECT

    QVector<QImage> currentPuzzleVector = QVector<QImage>();
    int currentWidth = -1;
    int currentHeight = -1;

    int selectedInt = -1;

    bool isCaptured = false;
    QPoint capturedPoint = QPoint();
    QPoint capturedCursorPoint = QPoint();
    QImage capturedImage = QImage();

    QVector<int> wrongPiecesVector = QVector<int>();

public:
    explicit PuzzleView(QWidget *parent = nullptr);

    QVector<QImage> getCurrentPuzzleVector() const;
    void setCurrentPuzzleVector(const QVector<QImage> &value);

    int getCurrentWidth() const;
    void setCurrentWidth(int value);

    int getCurrentHeight() const;
    void setCurrentHeight(int value);

    int getSelectedInt() const;
    void setSelectedInt(int value);

    QVector<int> getWrongPiecesVector() const;
    void setWrongPiecesVector(const QVector<int> &value);

signals:
    void placeIsSelectedSignal (int);
    void pieceToMoveSignal (int, int);
    void pieceToDeleteSignal (int);
    void pieceToRightPlaceSignal (int);

public slots:
    void newGameSlot();
    void repaintSlot(const QVector<QImage> &myVector, int myWidth, int myHeight, const QVector<int> &wrongVector);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // PUZZLEVIEW_H
