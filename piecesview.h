#ifndef PIECESVIEW_H
#define PIECESVIEW_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QImage>
#include <QDebug>
#include <QMouseEvent>

class PiecesView : public QWidget
{
    Q_OBJECT

    QVector<QImage> currentPieceVector = QVector<QImage>();
    int currentWidth = -1;
    int currentHeight = -1;

    QImage selectedPieceImage = QImage();
    int selectedInt = -1;

public:
    explicit PiecesView(QWidget *parent = nullptr);

    QVector<QImage> getCurrentPuzzleVector() const;
    void setCurrentPuzzleVector(const QVector<QImage> &value);

    int getCurrentWidth() const;
    void setCurrentWidth(int value);

    int getCurrentHeight() const;
    void setCurrentHeight(int value);

    QImage getSelectedPieceImage() const;
    void setSelectedPieceImage(const QImage &value);

    int getSelectedInt() const;
    void setSelectedInt(int value);

signals:

    void pieceIsSelectedSignal (QImage);

public slots:

    void newGameSlot();
    void repaintSlot(const QVector<QImage> &myVector, int myWidth, int myHeight);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

};

#endif // PIECESVIEW_H
