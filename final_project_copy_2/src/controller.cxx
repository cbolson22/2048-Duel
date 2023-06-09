#include "controller.hxx"


Controller::Controller()
        : model_1(),
          model_2(),
          view_(model_1, model_2)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{

   model_1.refresh_over();
   model_2.refresh_over();

   view_.draw(set);

}


// You can get a `Key` representing space with `ge211::Key::code(' ')`.
void
Controller::on_key(ge211::Key key)
{

    if(view_.get_screen_num() == 3) {
        if (key == ge211::Key::code('a')) {
            try {
                model_1.move_left();
            } catch(...) {

            }
        } else if(key == ge211::Key::code('w')) {
            try {
                model_1.move_up();
            } catch(...) {

            }
        } else if(key == ge211::Key::code('s')) {
            try {
                model_1.move_down();
            } catch(...) {

            }
        } else if(key == ge211::Key::code('d')) {
            try {
                model_1.move_right();
            } catch(...) {

            }
        } else if (key == ge211::Key::left()) {
            try {
                model_2.move_left();
            } catch(...) {

            }
        } else if(key == ge211::Key::up()) {
            try {
                model_2.move_up();
            } catch(...) {

            }
        } else if(key == ge211::Key::down()) {
            try {
                model_2.move_down();
            } catch(...) {

            }
        } else if(key == ge211::Key::right()) {
            try {
                model_2.move_right();
            } catch(...) {

            }
        }
    }
    ///Main Menu available after game ends
    else if(view_.get_screen_num() == 4) {
        if(key == ge211::Key::code('m')) {
            //make new models to start game over
            model_1 = Model();
            model_2 = Model();
            view_.set_screen_num(0);
        }
    }


    ///Main Menu page
    else if(key == ge211::Key::code('m')) {
        view_.set_screen_num(0);
    }

    ///Instruction page
    else if(key == ge211::Key::code('i')) {
        view_.set_screen_num(1);
    }

    /// STARTING GAME
    else if(key == ge211::Key::code(' ')) {
        view_.set_screen_num(3);
    }

}



View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}