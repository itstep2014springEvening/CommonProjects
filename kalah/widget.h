#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QLCDNumber>
#include <QPushButton>
#include <QLabel>
#include "engine.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void makeTurn(int id);
    void restartGame();
private:
    QVector<QLCDNumber *>firstPlayerPulls;
    QVector<QLCDNumber *>secondPlayerPulls;
    QVector<QPushButton *>firstPlayerButtons;
    QVector<QPushButton *>secondPlayerButtons;
    QPushButton *newGameButton;
    QLCDNumber *firstPlayerKalah;
    QLCDNumber *secondPlayerKalah;
    QLabel *player;
    Engine *engine;//logica igruli

    void display()const;
    static QString status(State state, int player);
};

#endif // WIDGET_H
