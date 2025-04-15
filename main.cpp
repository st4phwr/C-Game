//
//  main.cpp
//  TicTacToe02
//
//  Created by Stephanie Wang on 4/14/25.
//

#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for std::numeric_limits
#include <locale> // Required for std::wstring_convert and std::codecvt_utf8

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char player1Symbol;
    char player2Symbol;
    std::string player1Name;
    std::string player2Name;
    std::string currentPlayerName;
    int player1Score;
    int player2Score;
    bool gameOver;

public:
    TicTacToe(char symbol1 = 'X', char symbol2 = 'O') // Use default ASCII characters
        : board(3, std::vector<char>(3, ' ')),
          player1Symbol(symbol1),
          player2Symbol(symbol2),
          player1Name("Player 1"),
          player2Name("Player 2"),
          currentPlayerName(player1Name),
          player1Score(0),
          player2Score(0),
          gameOver(false) {}

    void setPlayerNames(const std::string& name1, const std::string& name2) {
        player1Name = name1;
        player2Name = name2;
        currentPlayerName = player1Name;
    }

    void setSymbols(char symbol1, char symbol2) {
        player1Symbol = symbol1;
        player2Symbol = symbol2;
    }

    void printBoard() const {
        std::cout << "\n";
        std::cout << " " << getDisplaySymbol(board[0][0]) << " | " << getDisplaySymbol(board[0][1]) << " | " << getDisplaySymbol(board[0][2]) << " \n";
        std::cout << "---+---+---\n";
        std::cout << " " << getDisplaySymbol(board[1][0]) << " | " << getDisplaySymbol(board[1][1]) << " | " << getDisplaySymbol(board[1][2]) << " \n";
        std::cout << "---+---+---\n";
        std::cout << " " << getDisplaySymbol(board[2][0]) << " | " << getDisplaySymbol(board[2][1]) << " | " << getDisplaySymbol(board[2][2]) << " \n\n";
    }

    bool makeMove(int row, int col) {
        // Check if the move is valid
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            return false;
        }

        // Make the move
        board[row][col] = (currentPlayerName == player1Name) ? player1Symbol : player2Symbol;

        // Switch players
        currentPlayerName = (currentPlayerName == player1Name) ? player2Name : player1Name;

        return true;
    }

    bool checkWin() {
        char current = (currentPlayerName == player2Name) ? player1Symbol : player2Symbol; // Check win for the player who just moved

        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == current && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                gameOver = true;
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == current && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                gameOver = true;
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == current && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            gameOver = true;
            return true;
        }

        if (board[0][2] == current && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            gameOver = true;
            return true;
        }

        return false;
    }

    bool checkDraw() {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') {
                    return false;
                }
            }
        }
        gameOver = true;
        return true;
    }

    std::string getCurrentPlayerName() const {
        return currentPlayerName;
    }

    bool isGameOver() const {
        return gameOver;
    }

    void printInstructions() const {
        std::cout << "Welcome to Tic Tac Toe!\n";
        std::cout << "Enter moves using row (0-2) and column (0-2)\n";
        std::cout << "Example: '1 1' for center position\n\n";
        std::cout << "Board positions:\n";
        std::cout << " 0,0 | 0,1 | 0,2 \n";
        std::cout << "-----|-----|-----\n";
        std::cout << " 1,0 | 1,1 | 1,2 \n";
        std::cout << "-----|-----|-----\n";
        std::cout << " 2,0 | 2,1 | 2,2 \n\n";
        std::cout << player1Name << "'s symbol: " << getDisplaySymbol(player1Symbol) << "\n";
        std::cout << player2Name << "'s symbol: " << getDisplaySymbol(player2Symbol) << "\n\n";
    }

    void printScore() const {
        std::cout << "\n--- Score ---\n";
        std::cout << player1Name << ": " << player1Score << "\n";
        std::cout << player2Name << ": " << player2Score << "\n";
        std::cout << "-------------\n";
    }

    void updateScore(bool player1Won) {
        if (player1Won) {
            player1Score++;
        } else {
            player2Score++;
        }
    }

    void resetGame() {
        for (auto& row : board) {
            for (char& cell : row) {
                cell = ' ';
            }
        }
        currentPlayerName = player1Name;
        gameOver = false;
    }

private:
    char getDisplaySymbol(char symbol) const {
        return symbol;
    }
};

int main() {
    TicTacToe game;
    std::string player1, player2;
    char ready1, ready2;
    char symbol1, symbol2;

    std::cout << "Enter Player 1's name: ";
    std::cin >> player1;
    std::cout << "Enter Player 1's symbol: ";
    std::cin >> symbol1;
    std::cout << "Enter Player 2's name: ";
    std::cin >> player2;
    std::cout << "Enter Player 2's symbol: ";
    std::cin >> symbol2;
    game.setPlayerNames(player1, player2);
    game.setSymbols(symbol1, symbol2);

    std::cout << player1 << ", are you ready? (y/n): ";
    std::cin >> ready1;
    std::cout << player2 << ", are you ready? (y/n): ";
    std::cin >> ready2;

    if (tolower(ready1) != 'y' || tolower(ready2) != 'y') {
        std::cout << "Not both players are ready. Exiting game.\n";
        return 0;
    }

    game.printInstructions();

    while (true) {
        game.resetGame();
        while (!game.isGameOver()) {
            game.printBoard();
            std::cout << game.getCurrentPlayerName() << "'s turn.\n";
            std::cout << "Enter row and column (0-2): ";

            int row, col;
            std::cin >> row >> col;

            // Clear input buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!game.makeMove(row, col)) {
                std::cout << "Invalid move! Try again.\n";
                continue;
            }

            if (game.checkWin()) {
                game.printBoard();
                std::cout << game.getCurrentPlayerName() << " wins!\n";
                game.updateScore(game.getCurrentPlayerName() == player1);
                break;
            }

            if (game.checkDraw()) {
                game.printBoard();
                std::cout << "It's a draw!\n";
                break;
            }
        }

        game.printScore();

        char playAgain;
        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;

        if (tolower(playAgain) != 'y') {
            std::cout << "Thanks for playing!\n";
            break;
        }
    }

    return 0;
}
