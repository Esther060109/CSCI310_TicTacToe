# CSCI310 Tic-Tac-Toe

This project implements a simple tic-tac-toe game in C++ using threads to model two players, `X` and `O`.

## Project goal

The goal of this assignment is to demonstrate key operating system concepts:

- protected shared memory
- thread synchronization
- mutex locking
- race-condition prevention
- concurrent gameplay behavior

## Files

- `main.cpp` - program entry point
- `Players.cpp` - player logic and board management

## How it works

The board is represented as a 3x3 character array:

```c++
char board[ROW][COL];
```

Each player thread is responsible for making moves on the shared board. A mutex is used to ensure that only one player updates or reads the board at a time, preventing data races and collisions.

## Build and run

From the project folder, compile the code with:

```bash
g++ main.cpp Players.cpp -o game -pthread
```

Then run the program:

```bash
./game
```

On Windows PowerShell:

```powershell
g++ main.cpp Players.cpp -o game
.\game.exe
```

## Notes

- The game is designed to show thread coordination rather than a fully optimized strategy-based AI.
- Random move generation is used for player moves in this assignment.
- The board should be checked after each move for a winner or a draw.
- The program uses modern C++ standard threading (std::thread and std::mutex) for thread synchronization.

## Example behavior

Each player thread:

1. chooses a move
2. checks whether the square is empty
3. locks the mutex before updating the board
4. prints the board
5. unlocks the mutex
6. repeats until the game ends

This demonstrates how threads cooperate safely when sharing memory.
