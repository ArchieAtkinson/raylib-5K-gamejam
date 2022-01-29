#include "player.hpp"
#include "game.hpp"



Player::Player(Vector2 _pos) : pos {_pos}, rec{calc_rec(_pos)}, direction{left}, current_water {max_water}
{
    player_texture = LoadTexture("../resources/wateringcan.png");
}

void Player::load_texture()
{
    
}

void Player::draw()
{
    if (player_texture.id == 0)
    {
        int width = 50;
        int height = 100;
        DrawRectangle(pos.x - width/2.0f,  pos.y - height/2.0f, width, height, PINK);
    }

    Rectangle source;

    if (direction == left)
        source = (Rectangle){0, 0, static_cast<float>(player_texture.width), static_cast<float>(player_texture.height)};
    if (direction == right)
        source = (Rectangle){0, 0, -static_cast<float>(player_texture.width), static_cast<float>(player_texture.height)};

    Rectangle des = (Rectangle){pos.x,  pos.y,  static_cast<float>(player_texture.width), static_cast<float>(player_texture.height)};
    Vector2 origin = (Vector2){player_texture.width / 2.0f, player_texture.height / 2.0f};
    DrawTexturePro(player_texture, source, des, origin, 0, WHITE);
    
    draw_water_bar();
}

void Player::update()
{
    rec = calc_rec(pos);
}

Rectangle Player::calc_rec(Vector2 _pos)
{
    return {_pos.x - player_texture.width / 2.0f, _pos.y - player_texture.height / 2.0f, static_cast<float>(player_texture.width),
                     static_cast<float>(player_texture.height)};
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

void Player::move(Vector2 dist)
{
    if (dist.x > 0)
        direction = right;
    else if (dist.x < 0)
        direction = left;
    Vector2 future_pos = {pos.x + dist.x, pos.y + dist.y};
    Rectangle future_rec = calc_rec(future_pos);
    future_rec = game::scale_rec(future_rec, 0.75);
    for (const Plant& plant: game::plant_collection)
    {
        if (CheckCollisionRecs(game::scale_rec(plant.rec, 0.10), future_rec) or CheckCollisionRecs(game::sink, future_rec) )
            return;
    }
    pos = future_pos;
}