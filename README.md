*This project has been created as part of the 42 curriculum by salzghou.*

---

# so_long 
## Description

`so_long` is a small 2D top-down game built in C using the **MiniLibX** graphical library. The player controls a character on a tile-based map and must collect all collectibles before reaching the exit. The project covers window management, event handling, texture rendering, and map parsing.

The map is loaded from a `.ber` file at runtime. The game validates the map structure, checks for a valid path using flood fill, then renders the world using XPM images.

| Character | Meaning |
|-----------|---------|
| `0` | Empty floor |
| `1` | Wall |
| `C` | Collectible |
| `E` | Exit |
| `P` | Player starting position |

---

## Instructions

### Requirements

- Linux
- `cc` (GCC or Clang)
- X11 development libraries

```bash
sudo apt install libx11-dev libxext-dev git
```

### Compilation

```bash
make        # build
make clean  # remove objects
make fclean # remove objects + binary
make re     # rebuild from scratch
```

MiniLibX is cloned automatically if the `minilibx-linux/` folder is missing.

### Running

```bash
./so_long maps/map.ber
```

### Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move up |
| `S` / `↓` | Move down |
| `A` / `←` | Move left |
| `D` / `→` | Move right |
| `ESC` | Quit |
| Window `×` | Quit |

### Gameplay

Collect all `C` tiles then step on `E` to win. The exit is always walkable but only triggers the win once all collectibles are picked up. Move count is printed to the shell after every step.

### Map rules

- Only characters `0 1 C E P` allowed
- Exactly `1 P`, `1 E`, at least `1 C`
- Must be rectangular and fully enclosed by walls
- Must have a valid path from `P` to all `C` and `E`

Any invalid map prints `Error\n` followed by an error message and exits cleanly.

---

## Resources

- [MiniLibX Linux](https://github.com/42Paris/minilibx-linux)
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Flood fill — Wikipedia](https://en.wikipedia.org/wiki/Flood_fill)
- [Free game assets — itch.io](https://itch.io/game-assets/free)

### AI usage

AI was used as a general assistant during development — for looking up MiniLibX function usage, understanding error messages, and getting suggestions on code structure. All generated content was reviewed and adapted manually.
