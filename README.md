# Archie's raylib 5K gamejam Game

## A Simple Plant Game

![Game Screenshot](assets/game_screenshot.PNG)

### Description

Keep your plants watered and happy!

### Features

 - Plants
 - Plants
 - Plants

### Controls

Keyboard:
 - WASD to move
 - Q to water plant and refill water

### Developers

 - Archie Atkinson - Everything but Music
 - Andrew Atkinson - Music

### Links

 - itch.io Release: $(itch.io Game Page)

### Running the Game
Requires:
- [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)
- CMake
- GCC
- sed (Comes with mingw)

#### Web
- `emcmake cmake -S . -B build_web -G Ninja -DPLATFORM=Web`
- `cmake --build build_web`
- `emrun build_web/GameJam.html`

#### Web
- `cmake -S . -B build -G Ninja -DPLATFORM=Desktop`
- `cmake --build build`
- `./build/GameJam.exe`


*Copyright (c) 2022 Archie Atkinson*    

---

*All content of this repo apart from the music (music is defined as the .wav files contained in this repo) and "background.png" are under the GNU Affero General Public 3.0 License. The music under the Creative Commons Attribution-NonCommercial 2.0 Generic License. "background.png" is from [pxfuel](https://www.pxfuel.com) and is under their [Terms of Use](https://www.pxfuel.com/terms-of-use).*