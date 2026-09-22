#include <iostream>
#include <thread>


// declare functions from Players.cpp
void Player1();
void Player2();
void display();

int main() {
    srand(time(nullptr)); //Seed random number generator NOLINT

    // Create threads
    std::thread t1(Player1);
    std::thread t2(Player2);

    // wait for both threads to finish
    t1.join();
    t2.join();

    std::cout << "Game Over!\n";
    display();
    return 0;
}