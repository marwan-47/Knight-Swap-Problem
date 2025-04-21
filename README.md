# ♞ Knight Swap Problem

A C++ and Qt-based interactive visualization of the classic **Knight Swap** puzzle. The goal is to swap the positions of white and black knights on a 4×3 chessboard using valid knight moves.

---

## 🧩 Problem Description

You are given:
- A 4×3 chessboard.
- 3 White Knights placed at the bottom row.
- 3 Black Knights placed at the top row.

**Objective:** Swap their positions using valid knight moves.

### ♟️ Rules:
- Knights move in standard L-shaped patterns.
- Knights **cannot capture** or jump over other pieces.
- Each move must land on an **empty cell**.
- **Optional**: Moves can alternate between white and black knights.

---

## 🎮 Features

✅ GUI built with **Qt Framework**  
✅ Start button to begin the knight-swapping animation  
✅ Checkbox for **Alternate Turns** mode  
✅ Dial to control **Animation Speed** (300ms – 2000ms)  
✅ Displays **Minimum Number of Moves** required  
✅ **Reset** button to restart the program  

---

## 🖥️ Installation & Build

### 💡 Requirements:
- C++ compiler
- Qt 5 or 6

### 🔧 Build Instructions:

```bash
# Clone the repository
git clone https://github.com/marwan-47/Knight-Swap-Problem.git
cd Knight-Swap-Problem

# Build with qmake (if using command line)
cmake
make

```

## 🚀 Usage

-Run the app.

-Click Start to begin solving the puzzle.

-Check the Alternate Turns box to toggle between white/black moves.

-Use the Dial to adjust animation speed.

-Observe the minimum number of moves.

-Hit Reset to start over.


