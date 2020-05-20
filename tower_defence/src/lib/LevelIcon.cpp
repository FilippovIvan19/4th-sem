#include "../headers/LevelIcon.h"

LevelIcon::LevelIcon() :
CommonElement(),
number_ ( 0 ),
locked_ (true)
{}

LevelIcon::LevelIcon(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites,
        int number, int pic_frame_width, int pic_frame_height, sf::Font *font) : 
CommonElement(window, x0, y0, *sprites->level_icon_sprite, pic_frame_width, pic_frame_height), 
number_ (number),
locked_ (true),
lock_elem_ (window, x0 + LEVEL_ICON_SIZE / 2, y0 + LEVEL_ICON_SIZE / 2,
    *sprites->lock_sprite, LEVEL_LOCK_PIC_SIZE, LEVEL_LOCK_PIC_SIZE)
// number_elem_ (window, x0 + LEVEL_ICON_SIZE / 2, y0 + LEVEL_ICON_SIZE / 2,
//     *sprites->lock_sprite, LEVEL_LOCK_PIC_SIZE, LEVEL_LOCK_PIC_SIZE)
{
    this->lock_elem_.set_origin_center();
    
    sf::Text txt(sf::String(std::to_string(number_ + 1)), *font, GLOBAL_SCALE_COEF * 40);
    number_text_ = txt;
    number_text_.setPosition(this->get_x() + LEVEL_ICON_SIZE / 2,
     this->get_y() + LEVEL_ICON_SIZE / 2);
    number_text_.setOrigin(number_text_.getGlobalBounds().width / 2,
        number_text_.getGlobalBounds().height / 2);
    number_text_.setFillColor(sf::Color::White);
    number_text_.setOutlineColor(sf::Color::Black);
    number_text_.setOutlineThickness(1);
    // window->draw(this->number_text_);
}

LevelIcon::~LevelIcon() {}

void LevelIcon::draw() const
{
    this->CommonElement::draw();
    if (this->locked_)
        this->lock_elem_.draw();
    this->window_->draw(this->number_text_);
}

void LevelIcon::set_lock(bool value)
{
    this->locked_ = value;
}

bool LevelIcon::is_locked() const
{
    return this->locked_;
}
