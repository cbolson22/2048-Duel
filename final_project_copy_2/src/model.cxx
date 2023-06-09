#include "model.hxx"

using namespace ge211;



Model::Model()
        : tiles(16,0),
          score(0),
          over(false)
{

    //randomize three spots

    for(int i = 0; i < 3; i++) {
        add_random_tile();
    }


}

void
Model::refresh_over()
{
    over = game_over();
}


void
Model::move_left()
{

    if (game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    std::vector<int> origional_vec;

    for(int i = 0; i < 16; i++) {
        origional_vec.push_back(tiles[i]);
    }

    for(int i = 0; i < 16 ; i++) {
        if((i) % 4 != 0) {
            int j = i;
            while((j) % 4 != 0 && tiles[j-1] == 0) {
                tiles[j-1] = tiles[j];
                tiles[j] = 0;
                j--;
            }
            if((j) % 4 != 0 && tiles[j] == tiles[j-1]) {
                tiles[j-1] *= 2;
                score += tiles[j-1];
                tiles[j] = 0;
            }
        }
    }

    bool valid = false;
    for(int i = 0; i < 16; i++) {
        if(origional_vec[i] != tiles[i]) {
            valid = true;
            break;
        }
    }
    if(valid) {
        add_random_tile();
    }

}

void
Model::move_up()
{
    if (game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    std::vector<int> origional_vec;

    for(int i = 0; i < 16; i++) {
        origional_vec.push_back(tiles[i]);
    }

    for(int i = 4; i < 16; i++) {
        int j = i;
        while(j > 3 && tiles[j-4] == 0) {
            tiles[j-4] = tiles[j];
            tiles[j] = 0;
            j -= 4;
        }
        if(j > 3 && tiles[j] == tiles[j-4]) {
            tiles[j-4] *= 2;
            score += tiles[j-4];
            tiles[j] = 0;
        }
    }


    bool valid = false;
    for(int i = 0; i < 16; i++) {
        if(origional_vec[i] != tiles[i]) {
            valid = true;
            break;
        }
    }
    if(valid) {
        add_random_tile();
    }

}


void
Model::move_down()
{
    if (game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }


    std::vector<int> origional_vec;

    for(int i = 0; i < 16; i++) {
        origional_vec.push_back(tiles[i]);
    }


    for(int i = 11; i >= 0; i--) {
        int j = i;
        while(j < 12 && tiles[j+4] == 0) {
            tiles[j+4] = tiles[j];
            tiles[j] = 0;
            j += 4;
        }
        if(j < 12 && tiles[j] == tiles[j+4]) {
            tiles[j+4] *= 2;
            score += tiles[j+4];
            tiles[j] = 0;
        }
    }


    bool valid = false;
    for(int i = 0; i < 16; i++) {
        if(origional_vec[i] != tiles[i]) {
            valid = true;
            break;
        }
    }
    if(valid) {
        add_random_tile();
    }

}


void
Model::move_right()
{
    if (game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }


    std::vector<int> origional_vec;

    for(int i = 0; i < 16; i++) {
        origional_vec.push_back(tiles[i]);
    }


    for(int i = 15; i >= 0; i--) {
        if((i+1) % 4 != 0) {
            int j = i;
            while((j+1) % 4 != 0 && tiles[j+1] == 0) {
                tiles[j+1] = tiles[j];
                tiles[j] = 0;
                j++;
            }
            if((j+1) % 4 != 0 && tiles[j] == tiles[j+1]) {
                tiles[j+1] *= 2;
                score += tiles[j+1];
                tiles[j] = 0;
            }
        }
    }



    bool valid = false;
    for(int i = 0; i < 16; i++) {
        if(origional_vec[i] != tiles[i]) {
            valid = true;
            break;
        }
    }
    if(valid) {
        add_random_tile();
    }

}


void
Model::add_random_tile()
{

    std::vector<int> vec;

    for(int i = 0; i < 16; i++) {
        if(tiles[i] == 0) {
            vec.push_back(i);
        }
    }

    int random = rand() % vec.size();


    int two_or_four = rand() % 10;


    if(two_or_four == 0) {
        tiles[vec[random]] = 4;
    } else {
        tiles[vec[random]] = 2;
    }


}


bool
Model::game_over()
{

    for(int i = 0; i < 16; i++) {
        if(tiles[i] == 0) {
            return false;
        }
    }

    for(int i = 0; i < 16; i++) {

        //check right for merge potential
        if((i+1) % 4 != 0) {
            if(tiles[i] == tiles[i+1]) {
                return false;
            }
        }

        //check left for merge potential
        if(i % 4 != 0) {
            if(tiles[i] == tiles[i-1]) {
                return false;
            }
        }

        //check up for merge potential
        if(i > 3) {
            if(tiles[i] == tiles[i-4]) {
                return false;
            }
        }

        //check down for merge potential
        if(i < 12) {
            if(tiles[i] == tiles[i+4]) {
                return false;
            }
        }

    }

    return true;
}