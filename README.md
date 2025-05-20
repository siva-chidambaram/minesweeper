# Terminal Minesweeper Game

A terminal-based **Minesweeper** game implemented in **C**. This game supports basic navigation, flagging, and cell opening functionality with difficulty and grid size selection. Designed to work on both **Windows** and **Unix-like systems** (Linux, macOS).


## 🎮 Features

- **Selectable grid sizes:** `8x8`, `12x12`, `16x16`
- **Difficulty levels:** Beginner, Intermediate, Expert
- **Flag** or **unflag** cells
- **Reveal** cells and **auto-expand** when empty
- **Win and Game Over detection**
- **Cross-platform `getch()` support** for keyboard interaction


## ⚙️ How It Works

- The game dynamically generates a minefield with a buffer around the border.
- Mines are randomly placed, and adjacent mine counts are calculated.
- A reference matrix tracks the status of each cell: closed, opened, flagged.
- Opening a mine reveals all mines and ends the game.
- Revealing all non-mine cells results in a win.


## 🕹️ Controls

- **Arrow Keys:** Navigate the grid
- **f:** Flag or unflag a cell
- **o:** Open (reveal) a cell


## 🛠️ Compilation Instructions

Make sure `gcc` is installed.

### Windows

Use any C compiler that supports `conio.h`

```bash
gcc main.c -o minesweeper
```

### Linux / macOS
`conio.h` is not available, so a replace using `termios.h`

```bash
gcc main.c -o minesweeper
```
