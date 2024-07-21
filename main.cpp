#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define PLAYER1 'X'
#define PLAYER2 'O'
#define EMPTY '_'

void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

int evaluate(const vector<vector<char>>& board) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == PLAYER1)
                return +10;
            else if (board[row][0] == PLAYER2)
                return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == PLAYER1)
                return +10;
            else if (board[0][col] == PLAYER2)
                return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == PLAYER1)
            return +10;
        else if (board[0][0] == PLAYER2)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == PLAYER1)
            return +10;
        else if (board[0][2] == PLAYER2)
            return -10;
    }

    return 0;
}

int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10)
        return score - depth;

    if (score == -10)
        return score + depth;

    if (!isMovesLeft(board))
        return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER1;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER2;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER1;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove.first = i;
                    bestMove.second = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

bool isWinner(vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool isDraw(vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

void playGame(int mode) {
    vector<vector<char>> board = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    cout << "Tic-Tac-Toe Game!" << endl;
    printBoard(board);

    bool player1Turn = true;
    while (true) {
        if (isWinner(board, PLAYER1)) {
            cout << "Player 1 wins!" << endl;
            break;
        }
        if (isWinner(board, PLAYER2)) {
            cout << "Player 2 wins!" << endl;
            break;
        }
        if (isDraw(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        if (player1Turn) {
            int row, col;
            if (mode == 1) {
                cout << "Player 1 (X) enter your move (row and column): ";
                cin >> row >> col;
            } else {
                cout << "Computer (X) is making a move..." << endl;
                pair<int, int> bestMove = findBestMove(board);
                row = bestMove.first;
                col = bestMove.second;
            }
            if (board[row][col] == EMPTY) {
                board[row][col] = PLAYER1;
                player1Turn = false;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        } else {
            int row, col;
            cout << "Player 2 (O) enter your move (row and column): ";
            cin >> row >> col;
            if (board[row][col] == EMPTY) {
                board[row][col] = PLAYER2;
                player1Turn = true;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }

        printBoard(board);
    }
}

int main() {
    int mode;
    cout << "Choose game mode: " << endl;
    cout << "1. Player1 vs Player2" << endl;
    cout << "2. Computer vs Player" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> mode;

    if (mode == 1 || mode == 2) {
        playGame(mode);
    } else {
        cout << "Invalid choice. Exiting." << endl;
    }

    return 0;
}
