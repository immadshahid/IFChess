#include <iostream>
#include <vector>
#include <string>
#include <limits>  // For clearing input buffer
#include <cmath>   // For abs()

using namespace std;

// Function to display the chessboard
void displayBoard(const vector<string>& board) {
    cout << "   a b c d e f g h" << endl;
    cout << "  -----------------" << endl;
    for (int rank = 0; rank < 8; ++rank) {
        cout << 8 - rank << " |";
        for (int file = 0; file < 8; ++file) {
            cout << board[rank][file] << " ";
        }
        cout << "|" << endl;
    }
    cout << "  -----------------" << endl;
    cout << "   a b c d e f g h" << endl;
    cout << endl;
}

// Function to initialize the chessboard
vector<string> initializeBoard() {
    vector<string> board(8, "........");
    board[0] = "rnbqkbnr";  // black pieces
    board[1] = "pppppppp";
    board[6] = "PPPPPPPP";
    board[7] = "RNBQKBNR";  // white pieces
    return board;
}

// Function to check if the move is valid
bool isValidMove(const vector<string>& board, const string& move, bool isWhiteTurn) {
    // Check if the move is in the correct format
    if (move.length() != 4) {
        return false;
    }

    int fromFile = move[0] - 'a';
    int fromRank = 8 - (move[1] - '0');
    int toFile = move[2] - 'a';
    int toRank = 8 - (move[3] - '0');

    // Check if the source and destination squares are within the board boundaries
    if (fromFile < 0 || fromFile > 7 || fromRank < 0 || fromRank > 7 ||
        toFile < 0 || toFile > 7 || toRank < 0 || toRank > 7) {
        return false;
    }

    // Check if the source and destination squares are different
    if (fromFile == toFile && fromRank == toRank) {
        return false;
    }

    // Check if the piece at the source square belongs to the player whose turn it is
    char piece = board[fromRank][fromFile];
    if (isWhiteTurn && (piece == '.' || islower(piece))) {
        return false;
    }
    if (!isWhiteTurn && (piece == '.' || isupper(piece))) {
        return false;
    }

    // Check specific move validation rules based on the piece type
    char targetPiece = board[toRank][toFile];

    switch (tolower(piece)) {
    case 'p': // Pawn
        if (piece == 'P') {
            // White pawn
            if (fromRank == 6) {
                // Check for double square move from initial position
                if (toRank == 4 && fromFile == toFile && board[5][fromFile] == '.') {
                    return true;
                }
            }
            // Check for regular single square move
            if (toRank == fromRank - 1 && fromFile == toFile && targetPiece == '.') {
                return true;
            }
            // Check for capture move
            if (toRank == fromRank - 1 && abs(toFile - fromFile) == 1 && islower(targetPiece)) {
                return true;
            }
        }
        else {
            // Black pawn
            if (fromRank == 1) {
                // Check for double square move from initial position
                if (toRank == 3 && fromFile == toFile && board[2][fromFile] == '.') {
                    return true;
                }
            }
            // Check for regular single square move
            if (toRank == fromRank + 1 && fromFile == toFile && targetPiece == '.') {
                return true;
            }
            // Check for capture move
            if (toRank == fromRank + 1 && abs(toFile - fromFile) == 1 && isupper(targetPiece)) {
                return true;
            }
        }
        break;
    case 'r': // Rook
        if (fromRank == toRank) {
            // Horizontal move
            int minFile = min(fromFile, toFile);
            int maxFile = max(fromFile, toFile);
            for (int file = minFile + 1; file < maxFile; ++file) {
                if (board[fromRank][file] != '.') {
                    return false;
                }
            }
            return true;
        }
        else if (fromFile == toFile) {
            // Vertical move
            int minRank = min(fromRank, toRank);
            int maxRank = max(fromRank, toRank);
            for (int rank = minRank + 1; rank < maxRank; ++rank) {
                if (board[rank][fromFile] != '.') {
                    return false;
                }
            }
            return true;
        }
        break;
    case 'n': // Knight
        if ((abs(toRank - fromRank) == 2 && abs(toFile - fromFile) == 1) ||
            (abs(toRank - fromRank) == 1 && abs(toFile - fromFile) == 2)) {
            return true;
        }
        break;
    case 'b': // Bishop
        if (abs(toRank - fromRank) == abs(toFile - fromFile)) {
            int rankDir = (toRank > fromRank) ? 1 : -1;
            int fileDir = (toFile > fromFile) ? 1 : -1;
            int rank = fromRank + rankDir;
            int file = fromFile + fileDir;
            while (rank != toRank) {
                if (board[rank][file] != '.') {
                    return false;
                }
                rank += rankDir;
                file += fileDir;
            }
            return true;
        }
        break;
    case 'q': // Queen
        if (fromRank == toRank) {
            // Horizontal move
            int minFile = min(fromFile, toFile);
            int maxFile = max(fromFile, toFile);
            for (int file = minFile + 1; file < maxFile; ++file) {
                if (board[fromRank][file] != '.') {
                    return false;
                }
            }
            return true;
        }
        else if (fromFile == toFile) {
            // Vertical move
            int minRank = min(fromRank, toRank);
            int maxRank = max(fromRank, toRank);
            for (int rank = minRank + 1; rank < maxRank; ++rank) {
                if (board[rank][fromFile] != '.') {
                    return false;
                }
            }
            return true;
        }
        else if (abs(toRank - fromRank) == abs(toFile - fromFile)) {
            int rankDir = (toRank > fromRank) ? 1 : -1;
            int fileDir = (toFile > fromFile) ? 1 : -1;
            int rank = fromRank + rankDir;
            int file = fromFile + fileDir;
            while (rank != toRank) {
                if (board[rank][file] != '.') {
                    return false;
                }
                rank += rankDir;
                file += fileDir;
            }
            return true;
        }
        break;
    case 'k': // King
        if (abs(toRank - fromRank) <= 1 && abs(toFile - fromFile) <= 1) {
            return true;
        }
        break;
    }

    return false;
}

// Function to perform a move on the chessboard
void makeMove(vector<string>& board, const string& move) {
    int fromFile = move[0] - 'a';
    int fromRank = 8 - (move[1] - '0');
    int toFile = move[2] - 'a';
    int toRank = 8 - (move[3] - '0');

    board[toRank][toFile] = board[fromRank][fromFile];
    board[fromRank][fromFile] = '.';
}

// Function to start the game
void start() {
    vector<string> board = initializeBoard();
    bool isWhiteTurn = true;
    string move;

    while (true) {
        displayBoard(board);

        if (isWhiteTurn) {
            cout << "White's turn (e2e4): ";
        }
        else {
            cout << "Black's turn (e7e5): ";
        }

        getline(cin, move);

        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (isValidMove(board, move, isWhiteTurn)) {
            makeMove(board, move);
            isWhiteTurn = !isWhiteTurn;
        }
        else {
            cout << "Invalid move. Please try again." << endl;

        }
    }
}

int main() {
    for (int i = 0; i <= 50; i++) {
        cout << char(350);
    }
    cout << endl;


    cout << "          WELCOME TO IFCHESS.com GAME!!!         " << endl;
    for (int i = 0; i <= 50; i++) {
        cout << char(350);
    }
    cout << endl;
    cout << "RULES FOR THE GAME:" << endl;
    cout << "1. CAPITAL represent WHITE." << endl
        << "2. small represent BLACK." << endl
        << "3. WHITE moves first." << endl
        << "4. Pawn Moves 1 block or 2 blocks at the first move and then 1 block in the following. " << endl
        << "5. Queen Moves vertical and horizontal and also diagonal " << endl
        << "6. King moves only 1 block, back and forth, left and right. " << endl
        << "7. Knight moves L- shape " << endl
        << "8. Biship moves diagonal " << endl
        << "9. Rook moves straight veritical and horizontal.  " << endl
        << "10. If the King is under attack , SAVE IT, if surrounded and no Moves left, it is CHECKMATE." << endl;

    for (int i = 0; i <= 50; i++) {
        cout << char(350);
    }
    cout << endl;

    start();


    return 0;
}