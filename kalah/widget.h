#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QLCDNumber>
#include <QPushButton>
class Engine;//predvaritel'noe oby'avlenie classa;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QVector<QLCDNumber *>firstPlayerPulls;
    QVector<QLCDNumber *>secondPlayerPulls;
    QVector<QPushButton *>firstPlayerButtons;
    QVector<QPushButton *>secondPlayerButtons;
    QLCDNumber *firstPlayerKalah;
    QLCDNumber *secondPlayerKalah;
    Engine *engine;//logica igruli

};

#endif // WIDGET_H
