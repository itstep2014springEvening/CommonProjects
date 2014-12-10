#include "widget.h"
#include <QtWidgets>
#include "engine.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      engine(nullptr)
{
    auto *mainlayout = new QHBoxLayout();
    setLayout(mainlayout);
    secondPlayerKalah = new QLCDNumber(2);
    secondPlayerKalah->setFixedWidth(125);
    mainlayout->addWidget(secondPlayerKalah);
    for (int i = 0; i < 6; ++i)
    {
        firstPlayerButtons.push_back(new QPushButton());//pushim knopon'ki
        secondPlayerButtons.push_back(new QPushButton());
        firstPlayerPulls.push_back(new QLCDNumber(2));//pushim lcdshki;
        firstPlayerPulls[i]->setFixedSize(100,150);
        secondPlayerPulls.push_back(new QLCDNumber(2));
        secondPlayerPulls[i]->setFixedSize(100,150);

    }

    for(int i=0;i<6;++i)
    {
        auto*lt=new QVBoxLayout();
        mainlayout->addLayout(lt);

        lt->addWidget(secondPlayerButtons[5-i]);
        lt->addWidget(secondPlayerPulls[5-i]);
        lt->addWidget(firstPlayerPulls[i]);
        lt->addWidget(firstPlayerButtons[i]);
    }
    firstPlayerKalah=new QLCDNumber(2);
    firstPlayerKalah->setFixedWidth(125);
    mainlayout->addWidget(firstPlayerKalah);


    setFixedSize(950,450);

    engine=new Engine();
    for (int i=0;i<6;++i)
    {
        firstPlayerPulls[i]->display(engine->at(0,i));
        secondPlayerPulls[i]->display(engine->at(1,i));
    }
}

Widget::~Widget()
{
    delete engine;
}
