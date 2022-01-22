# Archie's raylib 5K gamejam Game

https://kenney.nl/assets/toon-characters-1
https://kenney.nl/assets/generic-items

## $(Game Title)

![$(Game Title)](screenshots/screenshot000.png "$(Game Title)")

### Description

$(Your Game Description)

### Features

 - $(Game Feature 01)
 - $(Game Feature 02)
 - $(Game Feature 03)

### Controls

Keyboard:
 - $(Game Control 01)
 - $(Game Control 02)
 - $(Game Control 03)

### Screenshots

_TODO: Show your game to the world, animated GIFs recommended!._

### Developers

 - $(Developer 01) - $(Role/Tasks Developed)
 - $(Developer 02) - $(Role/Tasks Developed)
 - $(Developer 03) - $(Role/Tasks Developed)

### Links

 - YouTube Gameplay: $(YouTube Link)
 - itch.io Release: $(itch.io Game Page)
 - Steam Release: $(Steam Game Page)

### Running the Game
Requires:
- [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)
- CMake
- GCC
- sed (Comes with mingw)

#### Web
- `emcmake cmake -S . -B build_web -G Ninja -DPLATFORM=Web`
- `cmake --build build_web`
- `emrun build_webGameJam.html`

#### Web
- `cmake -S . -B build -G Ninja -DPLATFORM=Desktop`
- `cmake --build build`
- `./build/GameJam.exe`

For Live Reload:
- Live Server Extension
- File Watcher Extension

*Copyright (c) 2022 Archie Atkinson*