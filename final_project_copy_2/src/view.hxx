#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model_1, Model const& model_2);

    // View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    void draw(ge211::Sprite_set& set);

    void set_screen_num(int screen);
    int get_screen_num();

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_1_;
    Model const& model_2_;

    ///ge211::Timer const timer;
    std::chrono::system_clock::time_point start;
    ge211::Text_sprite timer_sprite;

    // background
    ge211::Rectangle_sprite full_background_sprite;;
    ge211::Rectangle_sprite first_board_background_sprite;
    ge211::Rectangle_sprite second_board_background_sprite;

    //tiles
    ge211::Rectangle_sprite background_tile;
    ge211::Rectangle_sprite tile_2;
    ge211::Rectangle_sprite tile_4;
    ge211::Rectangle_sprite tile_8;
    ge211::Rectangle_sprite tile_16;
    ge211::Rectangle_sprite tile_32;
    ge211::Rectangle_sprite tile_64;
    ge211::Rectangle_sprite tile_128;
    ge211::Rectangle_sprite tile_256;
    ge211::Rectangle_sprite tile_512;
    ge211::Rectangle_sprite tile_1024;
    ge211::Rectangle_sprite tile_2048;


    //tile text
    ge211::Text_sprite text_0;
    ge211::Text_sprite text_2;
    ge211::Text_sprite text_4;
    ge211::Text_sprite text_8;
    ge211::Text_sprite text_16;
    ge211::Text_sprite text_32;
    ge211::Text_sprite text_64;
    ge211::Text_sprite text_128;
    ge211::Text_sprite text_256;
    ge211::Text_sprite text_512;
    ge211::Text_sprite text_1024;
    ge211::Text_sprite text_2048;



    //text
    ge211::Text_sprite const main_menu_title_sprite;
    ge211::Text_sprite const press_space_sprite;
    ge211::Text_sprite const press_i_sprite;
    ge211::Text_sprite const press_m_sprite;


    ge211::Text_sprite const instruction_sprite_1;
    ge211::Text_sprite const instruction_sprite_2;
    ge211::Text_sprite const instruction_sprite_3;
    ge211::Text_sprite const instruction_sprite_4;
    ge211::Text_sprite const instruction_sprite_5;


    ge211::Text_sprite game_title_sprite;
    ge211::Text_sprite score_1_sprite;
    ge211::Text_sprite score_2_sprite;


    //game over screen
    ge211::Text_sprite p1_win_sprite;
    ge211::Text_sprite p2_win_sprite;
    ge211::Text_sprite tie_sprite;


    void draw_main_menu(ge211::Sprite_set& set);

    void draw_instruction_page(ge211::Sprite_set& set);

    void draw_game(ge211::Sprite_set& set);

    void draw_end_game(ge211::Sprite_set& set);

    Dimensions tile_dims() const;

};
