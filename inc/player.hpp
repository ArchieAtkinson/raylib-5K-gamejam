#pragma once
#include "raylib.h"


class Player{
    public:
      Player();
      void load_texture();
      void update();
      void draw();
      Rectangle get_rec();

      int current_water;
      Vector2 pos;
      static const int max_water = 1000;

    private:
      void draw_water_bar();
      int speed;
      Texture2D player_texture;
};