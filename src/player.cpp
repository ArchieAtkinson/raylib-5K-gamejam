#include "player.hpp"
#include "game.hpp"



Player::Player(Texture2D _player_texture) : player_texture{_player_texture}, pos{500,500}, current_water{max_water}
{

}

void Player::draw()
{
    DrawTexture(player_texture, pos.x - player_texture.width/2.0f,  pos.y - player_texture.height/2.0f, WHITE);

    draw_water_bar();
}

void Player::update()
{

}

Rectangle Player::get_rec()
{
    Rectangle rec = {pos.x - player_texture.width / 2.0f, pos.y - player_texture.height / 2.0f, static_cast<float>(player_texture.width),
                     static_cast<float>(player_texture.height)};
    return rec;
}

void Player::draw_water_bar()
{
    const int bar_width = 25;
    const int bar_length_max = 200;
    const int margin = 50;

    float water_per = (float)current_water / (float)max_water;
    int bar_length = water_per * 200;

    DrawRectangle(game::screen_width - margin, margin, bar_width, bar_length, BLUE);
}