#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;

private:
    Model model_1;
    Model model_2;
    View view_;


    void on_key(ge211::Key key) override;


    View::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

};
