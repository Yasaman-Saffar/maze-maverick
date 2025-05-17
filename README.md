# Project Name:  
**Maze-Maverick**

## Developed by:  
- Fateme Bakhshi  
- Yasaman Saffar

---

## Project Description

This project is a puzzle-solving game implemented in **C++**.  
The program begins with displaying a menu that allows the user to choose from several options, including:

- Creating new maps  
- Playing with existing or custom maps  
- Solving the maze  
- Viewing game history  
- Checking user information

---

## Map Creation

In this section, the user is asked to enter the number of rows, columns, and a custom name for the map.  
The map is then filled with random integers between **-3 and 3 (excluding 0)**.  
The generated map is saved as a file in the `"Maps"` folder.

---

## Game Mode

The user can either choose from existing maps or upload a custom map (with the same format as the built-in ones).  
After selecting a map, the game starts. Based on the rules, the user either wins or loses.  
(See the "How to Play" section for more details.)

---

## Maze Solver

Similar to the game mode, users can choose or upload a map, and the program will display a possible solution path.

- The solution path is always **L-shaped**, with a fixed length of **(rows + columns - 1)**.
- The path includes the **last row and the first column**, and is shown in **blue**.
- Obstacles are represented by `0`s, and there are randomly between **2 to 5 obstacles** placed **outside** the solution path.
- The **last cell** in the path contains the sum of all the cells on the path to ensure that at least one valid solution exists.

---

## View Game History

Displays the results of the **last 10 games** played.

---

## User Information

The user can enter a name and view statistics for that specific user.  
This data is updated after each game.

---

## Exit Option

The menu also includes an option to exit the program.

---

## How to Play

The game board is built based on the same structure as the maze solver, but the solution path is **not shown in blue** during the game.

- The user moves using the **W (up), A (left), S (down), D (right)** keys.
- Each cell visited is marked in **blue**.
- The **final cell** (destination) is marked in **red**.
- The user **cannot move out of bounds or onto cells with value 0** (obstacles).  
  If an invalid move is attempted, an **error message and a warning sound** will notify the user.

To win:
- The number of moves must exactly equal **(rows + columns - 1)**
- The **sum** of the visited cells must match the value in the final (red) cell.

Otherwise, the user loses.

---

## Project Contents

This project is delivered as a **ZIP file** which includes:

- The game executable
- `Maps/` folder containing a text file: `MapNames.txt`
- `Users/` folder containing a text file: `Usernames.txt`
- `README.txt` (this file)

 **Important:**  
Any changes to the folders or files (e.g., renaming, moving, editing, or deleting) may cause the program to malfunction.

