#include <iostream>
#include <thread>
#include <mutex>

#define ROW 3
#define COL 3

//initializing the board to be "empty"
char board[ROW][COL] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

//Global C++ Mutex
std::mutex mtx;
bool gameOver = false; //to stop both threads from printing who wins

void display()
{ 
    std::cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    std::cout << "---------\n";
    std::cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    std::cout << "---------\n";
    std::cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
}

//Check if a given player symbol ('X' or 'O') has won
int checkWin(char symbol) {
    //Check rows and columns
    for (int i = 0; i < ROW; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return 1;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return 1;
    }
    //Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return 1;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return 1;

    return 0;
    }

void Player1() {
    int row = 0; 
    int col = 0;

    while(true) {
        {
            // Lock the mutex for protected shared memory access
            std::lock_guard<std::mutex> lock(mtx);

            // If the game was already ended by the other thread, stop
            if (gameOver) break;

            // Pick a random spot until an empty one is found
            while(true) {
                row = rand() % ROW;
                col = rand() % COL;
                if(board[row][col] == ' ') {
                    board[row][col] = 'X';
                    break;
                }
            }
            // Check if this move won the game
            if (checkWin('X')) {
                std::cout << "Player 1 wins\n";
                gameOver=true;
                break;
            }
            if (checkWin('O')) {
                std::cout << "Player 2 wins\n";
                gameOver=true;
                break;
            }
            // Check if the board is full (for draw)
            int full = 0;
            for(int i = 0; i < ROW; i++) {
                for(int j = 0; j < COL; j++) {
                    if(board[i][j] != ' ') full += 1;
                }
            }
            if (full == ROW * COL) {
                std::cout << "It's a draw!\n";
                gameOver=true;
                break;
            }

            // Print board while inside the mutex lock
            std::cout << "Player X played at (" << row << ", " << col << "):\n";
            display();
            std::cout << "===================\n";
        } // Mutex automatically unlocks here

        // Small pause so the threads don't spin too fast
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

//just copy pasted Player1 logic and changed to 'O'
void Player2() {
    int row = 0;
    int col = 0;

    while(true) {
        {
            std::lock_guard<std::mutex> lock(mtx);

            if (gameOver) break;

            while(true) {
                row = rand() % ROW;
                col = rand() % COL;
                if(board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }

            if (checkWin('X')) {
                std::cout << "Player 1 wins\n";
                gameOver=true;
                break;
            }
            if (checkWin('O')) {
                std::cout << "Player 2 wins\n";
                gameOver=true;
                break;
            }
            int full = 0;
            for(int i = 0; i < ROW; i++) {
                for(int j = 0; j < COL; j++) {
                    if(board[i][j] != ' ') full += 1;
                }
            }
            if (full == ROW * COL) {
                std::cout << "It's a draw!\n";
                gameOver=true;
                break;
            }

            std::cout << "Player O played at (" << row << ", " << col << "):\n";
            display();
            std::cout << "===================\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

