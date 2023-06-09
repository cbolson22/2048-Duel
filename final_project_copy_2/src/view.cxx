#include "view.hxx"

// Convenient type alias:
using Color = ge211::Color;

// variables for drawing
static int const ofset_from_top = 100;
static int const ofset_from_bottom = 50;
static int const ofset_from_sides = 50;

static int const tile_size = 150;
static int space_between_tiles = 10;


//Colors for backgrounds
static Color const full_background_color {0,0,0};
static Color const first_board_background_color {242,171,145};
static Color const second_board_background_color {255,239,203};

//tile colors
static Color const background_tile_color {231, 225, 235};
static Color const tile_2_color {126,197,235};
static Color const tile_4_color {120,130,241};
static Color const tile_8_color {158,107,238};
static Color const tile_16_color {195,84,235};
static Color const tile_32_color {236,70,136};
static Color const tile_64_color {250,80,7};
static Color const tile_128_color {250,224,77};
static Color const tile_256_color {244, 214, 56};
static Color const tile_512_color {239,203,34};
static Color const tile_1024_color {233,193,13};
static Color const tile_2048_color {0,120,0};



//different screens showing (main menu, game, etc.)
static int screen = 0;


//for timer
static int time_limit = 60;


View::View(Model const& model_1, Model const& model_2)
        : //models
          model_1_(model_1),
          model_2_(model_2),

          //timer
          start(),

          //background sprite
          full_background_sprite({initial_window_dimensions().width,
                                  initial_window_dimensions().height},
                                 full_background_color),
          first_board_background_sprite({initial_window_dimensions().width /
                                          2, initial_window_dimensions().height},
                                         first_board_background_color),
          second_board_background_sprite({initial_window_dimensions().width /
                                            2, initial_window_dimensions().height},
                                        second_board_background_color),

          //tile sprites
          background_tile(tile_dims(), background_tile_color),
          tile_2(tile_dims(), tile_2_color),
          tile_4(tile_dims(), tile_4_color),
          tile_8(tile_dims(), tile_8_color),
          tile_16(tile_dims(), tile_16_color),
          tile_32(tile_dims(), tile_32_color),
          tile_64(tile_dims(), tile_64_color),
          tile_128(tile_dims(), tile_128_color),
          tile_256(tile_dims(), tile_256_color),
          tile_512(tile_dims(), tile_512_color),
          tile_1024(tile_dims(), tile_1024_color),
          tile_2048(tile_dims(), tile_2048_color),


          //tile text sprites
          text_0(" ", {"sans.ttf", 45}),
          text_2("2", {"sans.ttf", 45}),
          text_4("4", {"sans.ttf", 45}),
          text_8("8", {"sans.ttf", 45}),
          text_16("16", {"sans.ttf", 45}),
          text_32("32", {"sans.ttf", 45}),
          text_64("64", {"sans.ttf", 45}),
          text_128("128", {"sans.ttf", 45}),
          text_256("256", {"sans.ttf", 45}),
          text_512("512", {"sans.ttf", 45}),
          text_1024("1024", {"sans.ttf", 45}),
          text_2048("2048", {"sans.ttf", 45}),


        //text sprites
          main_menu_title_sprite("2048 Duel", {"sans.ttf", 140}),
          press_space_sprite("Press the 'Space Bar' to Start", {"sans.ttf", 35}),
          press_i_sprite("Press 'i' to see Instructions", {"sans.ttf", 25}),
          press_m_sprite("Press 'm' to go back to Main Menu", {"sans.ttf",
                                                                25}),

          //instruction screen
          instruction_sprite_1("HOW TO PLAY:", {"sans.ttf", 80}),
          instruction_sprite_2("Player 1 use 'w', 's', 'a', 'd' "
                               "to move the tiles on the left board.",
                               {"sans.ttf", 40}),
          instruction_sprite_3("Player 2 use the arrow keys to move the tiles "
                              "on the right board.", {"sans.ttf", 40}),
          instruction_sprite_4("Tiles with the same number merge into one when they touch.",
                              {"sans.ttf", 40}),
          instruction_sprite_5("First person to reach game over loses, or "
                               "highest score after timer ends wins!",
                              {"sans.ttf", 40}),


          //game over screen
          p1_win_sprite("Player 1 Wins!", {"sans.ttf", 45}),
          p2_win_sprite("Player 2 Wins" ,{"sans.ttf", 45}),
          tie_sprite("It's a Tie!" ,{"sans.ttf", 45})


{

}

void
View::draw(ge211::Sprite_set& set)
{
    if(screen == 0) {
        draw_main_menu(set);
    } else if(screen == 1){
        draw_instruction_page(set);
    } else if(screen == 3){
        draw_game(set);
    } else {
        draw_end_game(set);
    }

}


void
View::set_screen_num(int num)
{
    screen = num;
}

int
View::get_screen_num()
{
    return screen;
}


void
View::draw_main_menu(ge211::Sprite_set& set)
{
    //background color/sprite
    full_background_sprite.recolor({242,171,145});
    set.add_sprite(full_background_sprite, {0,0},-1);


    set.add_sprite(main_menu_title_sprite, {(initial_window_dimensions
                                                    ().width / 2) -
                                                    (main_menu_title_sprite
                                                    .dimensions().width / 2),
                                                    initial_window_dimensions
                                                    ().height/5});

    set.add_sprite(press_space_sprite,{(initial_window_dimensions
                                                ().width / 2) -
                                                (press_space_sprite
                                                .dimensions().width / 2),
                                       initial_window_dimensions
                                       ().height/2});

    set.add_sprite(press_i_sprite, {(initial_window_dimensions
                                            ().width / 2) -
                                            (press_i_sprite
                                            .dimensions().width / 2),
                                       initial_window_dimensions
                                               ().height/2 +
                                               press_space_sprite.dimensions
                                               ().height});


}



void
View::draw_instruction_page(ge211::Sprite_set& set)
{
    //background color/sprite
    full_background_sprite.recolor({100,203,129});
    set.add_sprite(full_background_sprite, {0,0},-1);


    int y = 100;
    set.add_sprite(instruction_sprite_1, {initial_window_dimensions().width / 2
                                                - (instruction_sprite_1
                                                .dimensions().width / 2),
                                                y});

    y += instruction_sprite_1.dimensions().height;
    set.add_sprite(instruction_sprite_2, {initial_window_dimensions().width / 2
                                                - (instruction_sprite_2
                                                .dimensions().width / 2),
                                                y});

    y += instruction_sprite_2.dimensions().height;
    set.add_sprite(instruction_sprite_3, {initial_window_dimensions().width / 2
                                                - (instruction_sprite_3
                                                .dimensions().width / 2),
                                                y});

    y += instruction_sprite_3.dimensions().height;
    set.add_sprite(instruction_sprite_4, {initial_window_dimensions().width / 2
                                                   - (instruction_sprite_4
                                                   .dimensions().width / 2),
                                                   y});

    y += instruction_sprite_4.dimensions().height;
    set.add_sprite(instruction_sprite_5, {initial_window_dimensions().width / 2
                                                    - (instruction_sprite_5
                                                    .dimensions().width / 2),
                                                    y});

    set.add_sprite(press_space_sprite, {initial_window_dimensions().width / 2
                                                    - (press_space_sprite
                                                   .dimensions().width / 2),
                                                   initial_window_dimensions
                                                   ().height -
                                                   (press_space_sprite
                                                   .dimensions().height * 3)});


    set.add_sprite(press_m_sprite, {20,
                                            initial_window_dimensions
                                                ().height -
                                                (press_m_sprite
                                                .dimensions().height * 2)});
}


void
View::draw_game(ge211::Sprite_set& set)
{

    first_board_background_sprite.recolor(first_board_background_color);
    second_board_background_sprite.recolor(second_board_background_color);


    //starts  clock when first play is made
    if(model_1_.score == 0 && model_2_.score == 0) {
        start = std::chrono::system_clock::now();
    }


    //get cur time and find seconds passed
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds_passed = now - start;


    //end game when someone loses or timer runs outor timer runs out
    if(model_1_.over || model_2_.over || seconds_passed.count() > time_limit) {
        screen = 4;
    }



    //left side background sprite
    set.add_sprite(first_board_background_sprite, {0,0},-1);

    //right side background sprite
    set.add_sprite(second_board_background_sprite, {initial_window_dimensions
                                                                ().width / 2,
                                                                0},-1);

    ge211::Font sans_35 = {"sans.ttf", 35};

    ge211::Text_sprite::Builder game_title_builder(sans_35);
    game_title_builder << "2048 Duel";
    game_title_builder.color({0, 0, 0});

    game_title_sprite.reconfigure(game_title_builder);

    //title sprite
    set.add_sprite(game_title_sprite, {(initial_window_dimensions().width /
                                        2) - (game_title_sprite.dimensions().width / 2),
                                       0}, 3);


    //timer sprite
    ge211::Font sans_25 = {"sans.ttf", 25};

    ge211::Text_sprite::Builder timer_builder(sans_25);

    if(model_1_.score == 0 && model_2_.score == 0) {
        timer_builder << "Time: " << time_limit;
    } else if(screen == 3) {
            timer_builder << "Time: " << (int)(time_limit - seconds_passed.count());
    } else {
        timer_builder << "Time: 0";
    }

    timer_builder.color({0, 0, 0});

    timer_sprite.reconfigure(timer_builder);


    set.add_sprite(timer_sprite, {(initial_window_dimensions().width / 2) -
                                       (timer_sprite.dimensions().width / 2),
                                       ofset_from_top - game_title_sprite
                                               .dimensions().height}, 3);


    //score sprites

    ge211::Text_sprite::Builder score_1_builder(sans_25);
    ge211::Text_sprite::Builder score_2_builder(sans_25);

    score_1_builder << "Score: " << model_1_.score;
    score_2_builder << "Score: " << model_2_.score;
    score_1_builder.color({0, 0, 0});
    score_2_builder.color({0, 0, 0});

    score_1_sprite.reconfigure(score_1_builder);
    score_2_sprite.reconfigure(score_2_builder);



    set.add_sprite(score_1_sprite, {ofset_from_sides +
                                    (2 * tile_size) - (score_1_sprite
                                    .dimensions().width / 2),
                                    ofset_from_top - score_1_sprite.dimensions
                                    ().height}, 3);

    set.add_sprite(score_2_sprite, {(initial_window_dimensions
                                    ().width / 2) + ofset_from_sides +
                                    (2 * tile_size) - (score_1_sprite
                                    .dimensions().width / 2),
                                    ofset_from_top - score_1_sprite.dimensions
                                    ().height}, 3);



    //left board
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {

            ge211::Rectangle_sprite* cur_sprite_pointer = &background_tile;

            ge211::Text_sprite* cur_text_sprite_pointer = &text_0;

            int index = i + (j*4);
            if(model_1_.tiles[index] == 0) {
                cur_sprite_pointer = &background_tile;
                cur_text_sprite_pointer = &text_0;
            } else if(model_1_.tiles[index] == 2) {
                cur_sprite_pointer = &tile_2;
                cur_text_sprite_pointer = &text_2;
            } else if(model_1_.tiles[index] == 4) {
                cur_sprite_pointer = &tile_4;
                cur_text_sprite_pointer = &text_4;
            } else if(model_1_.tiles[index] == 8) {
                cur_sprite_pointer = &tile_8;
                cur_text_sprite_pointer = &text_8;
            } else if(model_1_.tiles[index] == 16) {
                cur_sprite_pointer = &tile_16;
                cur_text_sprite_pointer = &text_16;
            } else if(model_1_.tiles[index] == 32) {
                cur_sprite_pointer = &tile_32;
                cur_text_sprite_pointer = &text_32;
            } else if(model_1_.tiles[index] == 64) {
                cur_sprite_pointer = &tile_64;
                cur_text_sprite_pointer = &text_64;
            } else if(model_1_.tiles[index] == 128) {
                cur_sprite_pointer = &tile_128;
                cur_text_sprite_pointer = &text_128;
            } else if(model_1_.tiles[index] == 256) {
                cur_sprite_pointer = &tile_256;
                cur_text_sprite_pointer = &text_256;
            } else if(model_1_.tiles[index] == 512) {
                cur_sprite_pointer = &tile_512;
                cur_text_sprite_pointer = &text_512;
            } else if(model_1_.tiles[index] == 1024) {
                cur_sprite_pointer = &tile_1024;
                cur_text_sprite_pointer = &text_1024;
            } else {
                cur_sprite_pointer = &tile_2048;
                cur_text_sprite_pointer = &text_2048;
            }

            //add color rect tile
            set.add_sprite(*cur_sprite_pointer,{ofset_from_sides +
                                       (i * tile_size),
                                       ofset_from_top + (j * tile_size)}, 0);

            //add text number
            set.add_sprite(*cur_text_sprite_pointer,{ofset_from_sides +
                                                (i * tile_size) + (tile_size
                                                / 2) -
                                                (cur_text_sprite_pointer->dimensions().width /
                                                2) - 10,
                                                ofset_from_top + (j *
                                                tile_size) + (tile_size
                                                / 2) -
                                                (cur_text_sprite_pointer->dimensions()
                                                .height / 2) - 10}, 2);

        }
    }



    //right board
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {

            ge211::Rectangle_sprite* cur_sprite_pointer = &background_tile;

            ge211::Text_sprite* cur_text_sprite_pointer = &text_0;

            int index = i + (j*4);
            if(model_2_.tiles[index] == 0) {
                cur_sprite_pointer = &background_tile;
                cur_text_sprite_pointer = &text_0;
            } else if(model_2_.tiles[index] == 2) {
                cur_sprite_pointer = &tile_2;
                cur_text_sprite_pointer = &text_2;
            } else if(model_2_.tiles[index] == 4) {
                cur_sprite_pointer = &tile_4;
                cur_text_sprite_pointer = &text_4;
            } else if(model_2_.tiles[index] == 8) {
                cur_sprite_pointer = &tile_8;
                cur_text_sprite_pointer = &text_8;
            } else if(model_2_.tiles[index] == 16) {
                cur_sprite_pointer = &tile_16;
                cur_text_sprite_pointer = &text_16;
            } else if(model_2_.tiles[index] == 32) {
                cur_sprite_pointer = &tile_32;
                cur_text_sprite_pointer = &text_32;
            } else if(model_2_.tiles[index] == 64) {
                cur_sprite_pointer = &tile_64;
                cur_text_sprite_pointer = &text_64;
            } else if(model_2_.tiles[index] == 128) {
                cur_sprite_pointer = &tile_128;
                cur_text_sprite_pointer = &text_128;
            } else if(model_2_.tiles[index] == 256) {
                cur_sprite_pointer = &tile_256;
                cur_text_sprite_pointer = &text_256;
            } else if(model_2_.tiles[index] == 512) {
                cur_sprite_pointer = &tile_512;
                cur_text_sprite_pointer = &text_512;
            } else if(model_2_.tiles[index] == 1024) {
                cur_sprite_pointer = &tile_1024;
                cur_text_sprite_pointer = &text_1024;
            } else {
                cur_sprite_pointer = &tile_2048;
                cur_text_sprite_pointer = &text_2048;
            }

            //add color rect tile
            set.add_sprite(*cur_sprite_pointer, {(initial_window_dimensions
                                             ().width / 2) +
                                    ofset_from_sides +
                                    (i * tile_size),
                                    ofset_from_top + (j * tile_size)}, 0);

            //add text number
            set.add_sprite(*cur_text_sprite_pointer, {(initial_window_dimensions().width / 2) + ofset_from_sides +
                                                    (i * tile_size)  + (tile_size
                                                    / 2) -
                                                    (cur_text_sprite_pointer->dimensions().width /
                                                     2) - 10,
                                                      ofset_from_top + (j *
                                                                        tile_size) + (tile_size
                                                                                      / 2) -
                                                      (cur_text_sprite_pointer->dimensions()
                                                                              .height / 2) - 10}, 2);

        }
    }

}



void
View::draw_end_game(ge211::Sprite_set& set)
{
    draw_game(set);


    Color const red_col {200,0,0};
    Color const green_col {0,200,0};

    ge211::Text_sprite* winner_text_sprite_pointer;
    if(model_1_.over) {
        winner_text_sprite_pointer = &p2_win_sprite;
        first_board_background_sprite.recolor(red_col);
        second_board_background_sprite.recolor(green_col);
    } else if(model_2_.over || model_1_.score > model_2_.score) {
        winner_text_sprite_pointer = &p1_win_sprite;
        first_board_background_sprite.recolor(green_col);
        second_board_background_sprite.recolor(red_col);
    } else if(model_1_.score < model_2_.score) {
        winner_text_sprite_pointer = &p2_win_sprite;
        first_board_background_sprite.recolor(red_col);
        second_board_background_sprite.recolor(green_col);
    } else {
        winner_text_sprite_pointer = &tie_sprite;
        first_board_background_sprite.recolor(green_col);
        second_board_background_sprite.recolor(green_col);
    }

    set.add_sprite(*winner_text_sprite_pointer, {initial_window_dimensions().width / 2 -
                                    ((*winner_text_sprite_pointer).dimensions
                                    ().width / 2),
                                    initial_window_dimensions().height -
                                    (*winner_text_sprite_pointer).dimensions().height},
                                    1);



    set.add_sprite(press_m_sprite, {20,
                                    initial_window_dimensions
                                            ().height -
                                    (press_m_sprite
                                             .dimensions().height)});
}





View::Dimensions
View::initial_window_dimensions() const
{
    View::Dimensions dims = {8 * tile_size,4 * tile_size};

    dims.width += (4 * ofset_from_sides);
    dims.height += (ofset_from_top + ofset_from_bottom);
    return dims;
}

View::Dimensions
View::tile_dims() const
{
    return {tile_size - space_between_tiles, tile_size - space_between_tiles};

}


std::string
View::initial_window_title() const
{

    return "2048 Versus";
}
