#include "widget.h"
#include <QtWidgets>
#include <QSignalMapper>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      engine(nullptr)
{
    auto *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    auto *statusLayout = new QHBoxLayout();
    mainLayout->addLayout(statusLayout);
    player = new QLabel(tr("ходит первый игрок"));
    statusLayout->addWidget(player);
    statusLayout->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::MinimumExpanding));
    newGameButton = new QPushButton();
    statusLayout->addWidget(newGameButton);
    auto *baseLayout = new QHBoxLayout();
    mainLayout->addLayout(baseLayout);
    secondPlayerKalah = new QLCDNumber(2);
    secondPlayerKalah->setFixedWidth(125);
    baseLayout->addWidget(secondPlayerKalah);
    for (int i = 0; i < 6; ++i)
    {
        firstPlayerButtons.push_back(new QPushButton());//pushim knopon'ki
        secondPlayerButtons.push_back(new QPushButton());
        firstPlayerPulls.push_back(new QLCDNumber(2));//pushim lcdshki;
        firstPlayerPulls[i]->setFixedSize(100, 150);
        secondPlayerPulls.push_back(new QLCDNumber(2));
        secondPlayerPulls[i]->setFixedSize(100, 150);

    }

    for(int i = 0; i < 6; ++i)
    {
        auto *lt = new QVBoxLayout();
        baseLayout->addLayout(lt);

        lt->addWidget(secondPlayerButtons[5 - i]);
        lt->addWidget(secondPlayerPulls[5 - i]);
        lt->addWidget(firstPlayerPulls[i]);
        lt->addWidget(firstPlayerButtons[i]);
    }
    firstPlayerKalah = new QLCDNumber(2);
    firstPlayerKalah->setFixedWidth(125);
    baseLayout->addWidget(firstPlayerKalah);


    setFixedSize(950, 450);

    engine = new Engine();
    display();

    auto *signalMapper = new QSignalMapper(this);
    for (int i = 0; i < 6; ++i)
    {
        signalMapper->setMapping(firstPlayerButtons[i], i);
        signalMapper->setMapping(secondPlayerButtons[i], i + 7);
    }
    for (int i = 0; i < 6; ++i)
    {
        connect(firstPlayerButtons[i],
                SIGNAL(clicked()),
                signalMapper,
                SLOT(map()));
        connect(secondPlayerButtons[i],
                SIGNAL(clicked()),
                signalMapper,
                SLOT(map()));
    }
    connect(signalMapper, SIGNAL(mapped(int)),
            this, SLOT(makeTurn(int)));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(restartGame()));
}

Widget::~Widget()
{
    delete engine;
}

void Widget::makeTurn(int id)
{
    int currentPlayer = engine->whichTurn();
    if(currentPlayer == id / 7)
    {
        engine->makeTurn(currentPlayer, id % 7);
        display();
    }

}

void Widget::restartGame()
{
    delete engine;
    engine = nullptr;
    engine = new Engine();
    display();
}

void Widget::display() const
{
    int currentPlayer = engine->whichTurn();
    State state = engine->check();
    player->setText(status(state, currentPlayer));
    newGameButton->setFlat(state == run);
    newGameButton->setDisabled(state == run);
    newGameButton->setText(state == run ? "" : tr("новая игра"));

    for (int i = 0; i < 6; ++i)
    {
        firstPlayerPulls[i]->display(engine->at(0, i));
        secondPlayerPulls[i]->display(engine->at(1, i));
        firstPlayerButtons[i]->setFlat(currentPlayer || engine->at(0, i) == 0);
        firstPlayerButtons[i]->setDisabled(currentPlayer || engine->at(0, i) == 0);
        secondPlayerButtons[i]->setFlat(!currentPlayer || engine->at(1, i) == 0);
        secondPlayerButtons[i]->setDisabled(!currentPlayer || engine->at(1, i) == 0);

    }
    firstPlayerKalah->display(engine->at(0, 6));
    secondPlayerKalah->display(engine->at(1, 6));

}

QString Widget::status(State state, int player)
{
    QString result;
    switch(state)
    {
    case run:
        if(player)
            result = QString(tr("ходит второй игрок"));
        else
            result = QString(tr("ходит первый игрок"));
        break;
    case firstwin:
        result = QString(tr("победил первый игрок"));
        break;
    case secondwin:
        result = QString(tr("победил второй игрок"));
        break;
    case draw:
        result = QString(tr("ничья"));
        break;
    }
    return result;

}
