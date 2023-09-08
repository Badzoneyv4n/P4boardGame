#include <iostream>
#include <vector>

const int ROWS = 6;
const int COLS = 7;

enum class Player { NONE, PLAYER1, PLAYER2 };

class Power4Game {
private:
    std::vector<std::vector<Player>> board;

public:
	Player currentPlayer;
    Power4Game() {
        board.resize(ROWS, std::vector<Player>(COLS, Player::NONE));
        currentPlayer = Player::PLAYER1;
    }

    void printBoard() {
        for (int i = ROWS - 1; i >= 0; i--) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == Player::NONE)
                    std::cout << ".";
                else if (board[i][j] == Player::PLAYER1)
                    std::cout << "X";
                else
                    std::cout << "O";

                std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "1 2 3 4 5 6 7\n";
    }

    bool isValidMove(int col) {
        return col >= 0 && col < COLS && board[ROWS - 1][col] == Player::NONE;
    }

    void makeMove(int col) {
        for (int i = 0; i < ROWS; i++) {
            if (board[i][col] == Player::NONE) {
                board[i][col] = currentPlayer;
                break;
            }
        }
    }

    bool checkWin() {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == currentPlayer) {
                    // Check horizontal
                    if (j + 3 < COLS && board[i][j + 1] == currentPlayer && board[i][j + 2] == currentPlayer && board[i][j + 3] == currentPlayer)
                        return true;

                    // Check vertical
                    if (i + 3 < ROWS && board[i + 1][j] == currentPlayer && board[i + 2][j] == currentPlayer && board[i + 3][j] == currentPlayer)
                        return true;

                    // Check diagonal (top-left to bottom-right)
                    if (i + 3 < ROWS && j + 3 < COLS && board[i + 1][j + 1] == currentPlayer && board[i + 2][j + 2] == currentPlayer && board[i + 3][j + 3] == currentPlayer)
                        return true;

                    // Check diagonal (top-right to bottom-left)
                    if (i + 3 < ROWS && j - 3 >= 0 && board[i + 1][j - 1] == currentPlayer && board[i + 2][j - 2] == currentPlayer && board[i + 3][j - 3] == currentPlayer)
                        return true;
                }
            }
        }
        return false;
    }

    bool isBoardFull() {
        for (int j = 0; j < COLS; j++) {
            if (board[ROWS - 1][j] == Player::NONE)
                return false;
        }
        return true;
    }

    void switchPlayer() {
        if (currentPlayer == Player::PLAYER1)
            currentPlayer = Player::PLAYER2;
        else
            currentPlayer = Player::PLAYER1;
    }
};

int main() {
    Power4Game game;
    int col;

    std::cout << "Welcome to Power4! The board is a 7x6 grid.\n";
    while (true) {
        game.printBoard();

        if (game.isBoardFull()) {
            std::cout << "It's a draw! The board is full.\n";
            break;
        }

        std::cout << "Player " << (game.currentPlayer == Player::PLAYER1 ? "X" : "O") << "'s turn. Enter column (1-7): ";
        std::cin >> col;
        col--; // Adjust for zero-based indexing

        if (game.isValidMove(col)) {
            game.makeMove(col);

            if (game.checkWin()) {
                game.printBoard();
                std::cout << "Player " << (game.currentPlayer == Player::PLAYER1 ? "X" : "O") << " wins!\n";
                break;
            }

            game.switchPlayer();
        } else {
            std::cout << "Invalid move. Try again.\n";
            goto jump;
        }
    }
    jump:

    return 0;
}