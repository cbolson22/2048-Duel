#include "model.hxx"
#include <catch.hxx>


Model empty_model();
int num_tiles(Model);

TEST_CASE("Moves work test")
{
    Model model = empty_model();

    model.tiles[0] = 8;
    model.tiles[1] = 8;
    model.tiles[7] = 32;
    model.tiles[10] = 128;

    //down
    model.move_down();

    //get rid of spawned random tile
    for(int i = 0; i < 12; i++) {
        model.tiles[i] = 0;
    }

    CHECK(model.tiles[12] == 8);
    CHECK(model.tiles[13] == 8);
    CHECK(model.tiles[14] == 128);
    CHECK(model.tiles[15] == 32);


    //left
    model.move_left();

    //get rid of spawned random tile
    for(int i = 0; i < 12; i++) {
        model.tiles[i] = 0;
    }
    model.tiles[15] = 0;

    CHECK(model.tiles[12] == 16);
    CHECK(model.tiles[13] == 128);
    CHECK(model.tiles[14] == 32);

    //up
    model.move_up();

    //get rid of spawned random tile
    for(int i = 3; i < 16; i++) {
        model.tiles[i] = 0;
    }

    CHECK(model.tiles[0] == 16);
    CHECK(model.tiles[1] == 128);
    CHECK(model.tiles[2] == 32);

    //right
    model.move_right();

    //get rid of spawned random tile
    for(int i = 4; i < 16; i++) {
        model.tiles[i] = 0;
    }
    model.tiles[0] = 0;

    CHECK(model.tiles[1] == 16);
    CHECK(model.tiles[2] == 128);
    CHECK(model.tiles[3] == 32);

}




TEST_CASE("Random spawn tiles test")
{

    ///check on empty model if extra blocks spawn (should be one new block per)

    Model model = empty_model();
    CHECK(num_tiles(model) == 0);

    model.tiles[0] = 8;
    model.tiles[7] = 32;
    model.tiles[10] = 128;
    CHECK(num_tiles(model) == 3);

    model.move_right();
    CHECK(num_tiles(model) == 4);

    model.move_left();
    CHECK(num_tiles(model) == 5);


    ///show exactly one new tile is spawned each valid move
    Model model_2 = empty_model();
    CHECK(num_tiles(model_2) == 0);

    model_2.tiles[0] = 8;
    model_2.tiles[1] = 8;
    model_2.tiles[7] = 32;
    model_2.tiles[10] = 128;
    CHECK(num_tiles(model_2) == 4);

    //all known tiles from above should be on the bottom row so check
    // everywhere else
    model_2.move_down();

    int new_tiles = 0;
    for(int i = 0; i < 12; i++) {
        if(model_2.tiles[i] != 0) {
            new_tiles ++;
        }
    }
    CHECK(new_tiles == 1);

}

TEST_CASE("Invalid move test")
{
    /// nothing should change when invalid move played on model

    //see if invalid right doesn't change anything
    Model model = empty_model();

    model.tiles[3] = 2;
    model.tiles[7] = 2;
    model.tiles[11] = 2;
    model.tiles[15] = 2;

    model.move_right();

    //everything the same (no added tiles)
    CHECK(model.tiles[3] == 2);
    CHECK(model.tiles[7] == 2);
    CHECK(model.tiles[11] == 2);
    CHECK(model.tiles[15] == 2);
    for(int i = 0; i < 16; i++) {
        if((i+1) %4 != 0) {
            CHECK(model.tiles[i] == 0);
        }
    }

    //see if invalid down doesn't change anything
    Model model_2 = empty_model();

    model_2.tiles[12] = 8;
    model_2.tiles[13] = 8;
    model_2.tiles[14] = 8;
    model_2.tiles[15] = 8;

    model_2.move_down();

    //everything the same (no added tiles)
    CHECK(model_2.tiles[12] == 8);
    CHECK(model_2.tiles[13] == 8);
    CHECK(model_2.tiles[14] == 8);
    CHECK(model_2.tiles[15] == 8);
    for(int i = 0; i < 12; i++) {
        CHECK(model_2.tiles[i] == 0);
    }

}


TEST_CASE("Game over")
{
    Model model = empty_model();

    CHECK(num_tiles(model) == 0);
    for(int i=0; i<11; ++i){
        model.tiles[i] = std::pow(2,i);
    }
    for(int j=11; j<16; ++j){
        model.tiles[j] = std::pow(2,j-11);
    }
    CHECK(num_tiles(model) == 16);
    model.refresh_over();
    CHECK(model.over == true);

}

TEST_CASE("Updating score")
{
    Model model = empty_model();

    CHECK(model.score == 0);
    model.tiles[0] = 2;
    model.tiles[1] = 2;
    model.tiles[4] = 16;
    CHECK(model.score == 0);
    model.move_left();
    CHECK(model.score == 4);

    for(int i=1; i < 4; ++i) {
        model.tiles[i] = 0;
    }
    for(int j=5; j<16; ++j) {
        model.tiles[j] = 0;
    }


    model.tiles[5] = 16;
    model.move_left();
    CHECK(model.score == 36);

}

TEST_CASE("Combining tiles")
{
    Model model = empty_model();

    CHECK(model.score == 0);
    model.tiles[0] = 2;
    model.tiles[1] = 2;
    model.tiles[2] = 2;
    model.tiles[3] = 2;

    model.move_left();
    CHECK(model.tiles[0] == 4);
    CHECK(model.tiles[1] == 4);
    CHECK(model.score == 8);

    model.move_left();
    CHECK(model.tiles[0] == 8);
    CHECK(model.score == 16);
}


Model
empty_model()
{
    Model model = Model();
    for(int i = 0; i < 16; i++) {
        model.tiles[i] = 0;
    }
    return model;
}


int
num_tiles(Model model)
{
    int ret = 0;
    for(int i = 0; i < 16; i++) {
        if(model.tiles[i] != 0) {
            ret ++;
        }
    }
    return ret;
}