#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 9;
const int NUM_COLORS = 7;
const int MIN_BALLS = 5;
const int MAX_BALLS = 7;

enum class Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE,
    PURPLE,
    CYAN
};

class Ball {
private:
    Color color;

public:
    Ball(Color color) : color(color) {}
    Ball() : color(Color::CYAN) {}
    Color getColor() const {
        return color;
    }
};

class Board {
private:
    std::vector<std::vector<Ball>> cells;

public:
    Board() {
        cells.resize(BOARD_SIZE, std::vector<Ball>(BOARD_SIZE));
    }

    void placeRandomBalls() {
        std::srand(std::time(nullptr));
        int numBalls = rand() % (MAX_BALLS - MIN_BALLS + 1) + MIN_BALLS;

        for (int i = 0; i < numBalls; i++) {
            int row = rand() % BOARD_SIZE;
            int col = rand() % BOARD_SIZE;
            Color color = static_cast<Color>(rand() % NUM_COLORS);
            cells[row][col] = Ball(color);
        }
    }

    void display() const {
        for (const auto& row : cells) {
            for (const auto& ball : row) {
                char symbol = getBallSymbol(ball);
                std::cout << symbol << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol) const {
        if (!isWithinBounds(startRow, startCol) || !isWithinBounds(endRow, endCol))
            return false;

        if (!isEmptyCell(startRow, startCol) || !isEmptyCell(endRow, endCol))
            return false;

        return hasPath(startRow, startCol, endRow, endCol);
    }

    bool hasPath(int startRow, int startCol, int endRow, int endCol) const {
        // Implement your path finding algorithm here
        // For simplicity, let's assume there is always a valid path
        return true;
    }

    bool isWithinBounds(int row, int col) const {
        return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
    }

    bool isEmptyCell(int row, int col) const {
        return cells[row][col].getColor() == Color::CYAN;
    }

    char getBallSymbol(const Ball& ball) const {
        switch (ball.getColor()) {
        case Color::RED:
            return 'R';
        case Color::GREEN:
            return 'G';
        case Color::BLUE:
            return 'B';
        case Color::YELLOW:
            return 'Y';
        case Color::ORANGE:
            return 'O';
        case Color::PURPLE:
            return 'P';
        case Color::CYAN:
            return '-';
        }
        return '-';
    }
};

class Game {
private:
    Board board;
    int score;

public:
    Game() : score(0) {
        board.placeRandomBalls();
    }

    void play() {
        while (true) {
            std::cout << "Current Score: " << score << std::endl;
            board.display();

            int startRow, startCol, endRow, endCol;
            std::cout << "Enter start position (row col): ";
            std::cin >> startRow >> startCol;
            std::cout << "Enter end position (row col): ";
            std::cin >> endRow >> endCol;

            if (board.isValidMove(startRow, startCol, endRow, endCol)) {
                // Perform the move and update the score
                // Implement your move logic here
                // ...

                score += 1;  // Increment the score for each removed ball
            }
            else {
                std::cout << "Invalid move. Try again." << std::endl;
            }

            if (isGameOver()) {
                std::cout << "Game Over! Board is full." << std::endl;
                break;
            }
        }
    }

    bool isGameOver() const {
        // Check if the board is full (no empty cells)
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (board.isEmptyCell(row, col))
                    return false;
            }
        }
        return true;
    }
};

int main() {
    Game game;
    game.play();

    return 0;
}
