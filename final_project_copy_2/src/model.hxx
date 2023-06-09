#pragma once

#include <ge211.hxx>

class Model
{
public:
    Model();

    std::vector<int> tiles;

    int score;

    bool over;

    void refresh_over();


    void move_left();
    void move_up();
    void move_down();
    void move_right();


private:

    void add_random_tile();

    bool game_over();

};
