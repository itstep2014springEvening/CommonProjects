#include "engine.h"

Engine::Engine()
{
    for (int i = 0; i < 6; ++i)
    {
        array[i] = array[i + 7] = 6;

    }
    array[6] = array[13] = 0;
    currentPlayer = 0;
}

int Engine::whichTurn() const
{
    return currentPlayer;
}

int nextPull(int player, int pull)//ukazatel' na next kletku;
{
    if (pull == 5)
    {
        return player == 0 ? 6 : 7;
    }
    if(pull == 12)
    {
        return player == 1 ? 13 : 0;
    }
    return pull + 1;
}

void Engine::makeTurn(int player, int pull)
{
    if(player == currentPlayer &&
            pull < 6 &&
            array[player * 7 + pull])//opredeleniye verha i niza v kalahe
    {
        int hand = array[player * 7 + pull];
        int currentPull = player * 7 + pull;
        array[player * 7 + pull] = 0;
        while(hand)
        {
            currentPull = nextPull(player, currentPull);
            ++array[currentPull];
            --hand;
        }
        if(currentPull != 7 && currentPull != 13)
        {
            currentPlayer = 1 - player;
        }
        if(array[currentPull] == 1 &&
                currentPlayer / 7 == player &&
                array[(currentPull + 7) % 14])
        {
            array[player * 7 + 6]
            +=
                array[currentPull]
                + array[(currentPull + 7) % 14];
        }
        int sumFirst = 0, sumSecond = 0;
        for(int i = 0; i < 6; ++i)
        {
            sumFirst += array[i];
            sumSecond += array[i + 7];
        }
        if(sumFirst == 0 || sumSecond == 0)
        {
            array[6] += sumFirst;
            array[13] += sumSecond;
            for(int i = 0; i < 6; ++i)
            {
                array[i] = 0;
                array[i + 7] = 0;
            }
        }

    }

}

int Engine::at(int player, int pull) const
{
    return array[player * 7 + pull];
}

State Engine::check() const
{
    for(int i = 0; i < 6; ++i)
    {
        if(array[i] || array[i + 7])
        {
            return run;
        }
    }
    if(array[6] < array[13])
    {
        return secondwin;
    }
    if(array[6] > array[13])
    {
        return firstwin;
    }
    return draw;
}
