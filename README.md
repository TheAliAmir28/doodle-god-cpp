# 🧪 Doodle God (C++ Console Game)

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![License](https://img.shields.io/badge/Use-Educational-lightgrey)

## 📌 Overview
**Doodle God** is a C++ console game inspired by the classic element-combining puzzler.  
You start with the four primaries — **Air, Earth, Fire, Water** — and combine them to discover new elements. The game reads a recipe list and lets you experiment to unlock all possible elements.

Examples:
- `Fire + Earth → Lava`
- `Water + Earth → Swamp`
- `Computer + Human → Cyborg`

---

## 🚀 Features
- **Element Combination System** — merge discovered elements to unlock new ones
- **Recipe Database** — pulls combinations from `proj2_recipes.txt`
- **Progress & Stats** — attempts, repeats, total discovered, and completion %
- **Menu-Driven UI** — list elements, combine, and view score
- **Easily Extensible** — add your own recipes by editing the text file

---

## 📂 Project Structure
```
DoodleGod.cpp
DoodleGod.h
Element.h
Game.cpp
Game.h
proj2.cpp              # Entry point
proj2_recipes.txt      # Recipe database (Result,Element1,Element2)
README.md
```

---

## 🧠 Architecture (Quick Tour)
- **Element** (struct): holds `m_name`, `m_element1`, `m_element2`.
- **DoodleGod** (class): tracks player name, attempts/repeats, known elements, and provides utilities to list/check/add elements.
- **Game** (class): loads recipes, runs the menu loop, handles combining logic, and prints score/progress.

> By default the game loads **139** elements from the recipes file and seeds your inventory with Air, Earth, Fire, and Water.

---

## 🛠️ Build & Run

### Prereqs
- C++ compiler supporting C++17 (e.g., `g++`, `clang++`, MSVC)

### Compile (Linux/macOS)
```bash
g++ -std=c++17 proj2.cpp Game.cpp DoodleGod.cpp -o doodlegod
```

### Compile (Windows - MinGW)
```bash
g++ -std=c++17 proj2.cpp Game.cpp DoodleGod.cpp -o doodlegod.exe
```

### Run
```bash
./doodlegod
# or on Windows
doodlegod.exe
```

> Ensure `proj2_recipes.txt` is **in the same directory** as the executable so the game can load the recipes.

---

## 🎮 Gameplay Flow
At launch you’ll see the ASCII title and be prompted to name your Doodle God. Then you’ll loop through a simple menu:

```
1. Display the Doodle God's Elements
2. Attempt to Combine Elements
3. See Score
4. Quit
```

- **Display Elements** — shows a numbered list of everything you’ve discovered
- **Combine Elements** — pick two by number to attempt a merge (works in any order)
- **See Score** — prints attempts, repeats, count discovered, and completion %

If a valid recipe is found and it’s **new**, it’s added to your collection. If you’ve already discovered it, the game increments a **repeat** counter.

---

## 📑 Recipes File Format (`proj2_recipes.txt`)
Each line is a single recipe in **CSV** form:

```
Result,Element1,Element2
```

Examples:
```
Lava,Fire,Earth
Swamp,Water,Earth
Cyborg,Computer,Human
```

**Tips**
- Order doesn’t matter when combining (A+B == B+A)
- You can extend the game by appending more lines in the same format

---

## 🔎 Example Session (abridged)
```
**************************************************************
 DDD   OOOO  OOOO  DDD   L    EEEE  GGGG  OOOO  DDD
 D  D  O  O  O  O  D  D  L    E     G     O  O  D  D
 D  D  O  O  O  O  D  D  L    EEEE  G GG  O  O  D  D
 D  D  O  O  O  O  D  D  L    E     G  G  O  O  D  D
 DDD   OOOO  OOOO  DDD   LLLL EEEE  GGGG  OOOO  DDD
**************************************************************

What would you like to do?
1. Display the Doodle God's Elements
2. Attempt to Combine Elements
3. See Score
4. Quit

Which element would you like to merge?
To list known elements, enter -1
```

---

## ⚖️ License / Use
This codebase was created for **educational purposes** as part of **CMSC 202**.  
You’re welcome to use and modify it for learning and portfolio demonstrations.

---

## 👨‍💻 Author
**Ali Amir**  
codepirate2028@gmail.com
