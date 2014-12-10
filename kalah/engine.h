#ifndef ENGINE_H
#define ENGINE_H

enum State {run = -1, firstwin, secondwin, draw};

class Engine
{
public:
    // Great VI
    Engine();
    Engine(const Engine &other) = default;
    Engine &operator=(const Engine &other) = default;
    Engine(Engine &&other) = default;
    Engine &operator=(Engine && other) = default;
    ~Engine() = default;
    // /Great VI

    int whichTurn() const;
    void makeTurn(int player, int pull);
    int at(int player , int pull) const;
    State check() const;
private:
    int array[14];
    int currentPlayer;

};

#endif // ENGINE_H
