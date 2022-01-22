#include "player.hpp"




Player::Player(Texture2D _player_texture) : player_texture{_player_texture}, pos{500,500}, current_water{max_water}
{

}

void Player::draw()
{
    // Vector2 sprite_size = {(float)player_texture.width / 9.0f, (float)player_texture.height / 5.0f};
    // Rectangle frame_rec = { 0.0f, 0.0f, sprite_size.x, sprite_size.y};
    // frame_rec.x = (float)sprite.x*sprite_size.x;
    // frame_rec.y = (float)sprite.y*sprite_size.y;

    DrawTexture(player_texture, pos.x - player_texture.width/2.0f,  pos.y - player_texture.height/2.0f, WHITE);
    DrawCircle(pos.x, pos.y, 10, GREEN);

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