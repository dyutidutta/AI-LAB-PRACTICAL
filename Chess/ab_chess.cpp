#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <string>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>

// Define if not available
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#endif

using namespace std;

const int BOARD_SIZE = 8;
const int INF = 999999;

enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum Color { NONE, WHITE, BLACK };

struct Piece {
    PieceType type;
    Color color;
    
    Piece() : type(EMPTY), color(NONE) {}
    Piece(PieceType t, Color c) : type(t), color(c) {}
};

struct Move {
    int fromRow, fromCol, toRow, toCol;
    PieceType promotion;
    
    Move() : fromRow(-1), fromCol(-1), toRow(-1), toCol(-1), promotion(EMPTY) {}
    Move(int fr, int fc, int tr, int tc, PieceType p = EMPTY) 
        : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), promotion(p) {}
    
    bool equals(const Move& other) const {
        return fromRow == other.fromRow && fromCol == other.fromCol && 
               toRow == other.toRow && toCol == other.toCol && promotion == other.promotion;
    }
    
    string toString() const {
        string result = "";
        result += char('a' + fromCol);
        result += char('0' + (8 - fromRow));
        result += " to ";
        result += char('a' + toCol);
        result += char('0' + (8 - toRow));
        if (promotion != EMPTY) result += "=Q";
        return result;
    }
};

// Console setup function
void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

// Piece-square tables for positional evaluation
const int PAWN_TABLE[64] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
};

const int KNIGHT_TABLE[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

const int BISHOP_TABLE[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

const int ROOK_TABLE[64] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    0,  0,  0,  5,  5,  0,  0,  0
};

const int QUEEN_TABLE[64] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
    0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

const int KING_TABLE_MIDDLEGAME[64] = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
};

const int KING_TABLE_ENDGAME[64] = {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-30
};

class ChessBoard {
private:
    Piece board[BOARD_SIZE][BOARD_SIZE];
    Color currentTurn;
    int whiteKingRow, whiteKingCol, blackKingRow, blackKingCol;

public:
    ChessBoard() {
        srand(time(0));
        setupConsole();  // Setup console for Unicode
        initializeBoard();
        currentTurn = WHITE;
    }

    void initializeBoard() {
        // Clear board
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = Piece(EMPTY, NONE);
            }
        }

        // Place pieces
        PieceType backRank[8] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
        
        for (int i = 0; i < 8; i++) {
            board[0][i] = Piece(backRank[i], BLACK);
            board[1][i] = Piece(PAWN, BLACK);
            board[6][i] = Piece(PAWN, WHITE);
            board[7][i] = Piece(backRank[i], WHITE);
        }
        
        whiteKingRow = 7; whiteKingCol = 4;
        blackKingRow = 0; blackKingCol = 4;
    }

    string getPieceSymbol(const Piece& piece) const {
        if (piece.type == EMPTY) return " ";
        
        // Unicode chess symbols
        if (piece.color == WHITE) {
            switch (piece.type) {
                case KING:   return "♔";
                case QUEEN:  return "♕";
                case ROOK:   return "♖";
                case BISHOP: return "♗";
                case KNIGHT: return "♘";
                case PAWN:   return "♙";
                default:     return " ";
            }
        } else {  // BLACK
            switch (piece.type) {
                case KING:   return "♚";
                case QUEEN:  return "♛";
                case ROOK:   return "♜";
                case BISHOP: return "♝";
                case KNIGHT: return "♞";
                case PAWN:   return "♟";
                default:     return " ";
            }
        }
    }

    // Keep the old method for compatibility
    char getPieceChar(const Piece& piece) const {
        if (piece.type == EMPTY) return '.';
        
        char symbols[7] = {'.', 'P', 'R', 'N', 'B', 'Q', 'K'};
        char ch = symbols[piece.type];
        return (piece.color == BLACK) ? tolower(ch) : ch;
    }

    void displayBoard() const {
        cout << "\n    a b c d e f g h\n";
        cout << "  +-----------------+\n";
        
        for (int row = 0; row < BOARD_SIZE; row++) {
            cout << (8 - row) << " | ";
            for (int col = 0; col < BOARD_SIZE; col++) {
                cout << getPieceSymbol(board[row][col]) << " ";
            }
            cout << "| " << (8 - row) << "\n";
        }
        
        cout << "  +-----------------+\n";
        cout << "    a b c d e f g h\n\n";
    }

    bool isValidPosition(int row, int col) const {
        return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
    }

    Piece getPiece(int row, int col) const {
        if (!isValidPosition(row, col)) return Piece();
        return board[row][col];
    }

    void setPiece(int row, int col, const Piece& piece) {
        if (isValidPosition(row, col)) {
            board[row][col] = piece;
            if (piece.type == KING) {
                if (piece.color == WHITE) {
                    whiteKingRow = row; whiteKingCol = col;
                } else {
                    blackKingRow = row; blackKingCol = col;
                }
            }
        }
    }

    Color getCurrentTurn() const { return currentTurn; }
    void switchTurn() { currentTurn = (currentTurn == WHITE) ? BLACK : WHITE; }

    bool isSquareAttacked(int row, int col, Color attackingColor) const {
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                Piece piece = board[r][c];
                if (piece.color == attackingColor) {
                    if (canPieceAttack(r, c, row, col)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool canPieceAttack(int fromRow, int fromCol, int toRow, int toCol) const {
        Piece piece = board[fromRow][fromCol];
        int dr = toRow - fromRow;
        int dc = toCol - fromCol;

        switch (piece.type) {
            case PAWN: {
                int direction = (piece.color == WHITE) ? -1 : 1;
                return (dr == direction && abs(dc) == 1);
            }
            case ROOK:
                return (dr == 0 || dc == 0) && isPathClear(fromRow, fromCol, toRow, toCol);
            case BISHOP:
                return (abs(dr) == abs(dc)) && isPathClear(fromRow, fromCol, toRow, toCol);
            case QUEEN:
                return ((dr == 0 || dc == 0) || (abs(dr) == abs(dc))) && 
                       isPathClear(fromRow, fromCol, toRow, toCol);
            case KNIGHT:
                return (abs(dr) == 2 && abs(dc) == 1) || (abs(dr) == 1 && abs(dc) == 2);
            case KING:
                return abs(dr) <= 1 && abs(dc) <= 1;
            default:
                return false;
        }
    }

    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol) const {
        int dr = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
        int dc = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
        
        int r = fromRow + dr;
        int c = fromCol + dc;
        
        while (r != toRow || c != toCol) {
            if (board[r][c].type != EMPTY) return false;
            r += dr;
            c += dc;
        }
        return true;
    }

    bool isInCheck(Color color) const {
        int kingRow, kingCol;
        if (color == WHITE) {
            kingRow = whiteKingRow; kingCol = whiteKingCol;
        } else {
            kingRow = blackKingRow; kingCol = blackKingCol;
        }
        return isSquareAttacked(kingRow, kingCol, color == WHITE ? BLACK : WHITE);
    }

    vector<Move> getLegalMoves() const {
        vector<Move> moves;
        
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                Piece piece = board[r][c];
                if (piece.color == currentTurn) {
                    vector<Move> pieceMoves = getPieceMoves(r, c);
                    for (size_t i = 0; i < pieceMoves.size(); i++) {
                        if (isLegalMove(pieceMoves[i])) {
                            moves.push_back(pieceMoves[i]);
                        }
                    }
                }
            }
        }
        return moves;
    }

    vector<Move> getPieceMoves(int row, int col) const {
        vector<Move> moves;
        Piece piece = board[row][col];

        switch (piece.type) {
            case PAWN:
                addPawnMoves(moves, row, col);
                break;
            case ROOK:
                {
                    static const int rookDirections[] = {0,1, 0,-1, 1,0, -1,0};
                    addSlidingMoves(moves, row, col, 4, rookDirections);
                }
                break;
            case BISHOP:
                {
                    static const int bishopDirections[] = {1,1, 1,-1, -1,1, -1,-1};
                    addSlidingMoves(moves, row, col, 4, bishopDirections);
                }
                break;
            case QUEEN:
                {
                    static const int queenDirections[] = {0,1, 0,-1, 1,0, -1,0, 1,1, 1,-1, -1,1, -1,-1};
                    addSlidingMoves(moves, row, col, 8, queenDirections);
                }
                break;
            case KNIGHT:
                addKnightMoves(moves, row, col);
                break;
            case KING:
                addKingMoves(moves, row, col);
                break;
        }
        return moves;
    }

    void addPawnMoves(vector<Move>& moves, int row, int col) const {
        Color color = board[row][col].color;
        int direction = (color == WHITE) ? -1 : 1;
        int startRow = (color == WHITE) ? 6 : 1;
        int promotionRow = (color == WHITE) ? 0 : 7;

        // Forward move
        if (isValidPosition(row + direction, col) && board[row + direction][col].type == EMPTY) {
            if (row + direction == promotionRow) {
                moves.push_back(Move(row, col, row + direction, col, QUEEN));
            } else {
                moves.push_back(Move(row, col, row + direction, col));
            }

            // Double forward from start
            if (row == startRow && board[row + 2 * direction][col].type == EMPTY) {
                moves.push_back(Move(row, col, row + 2 * direction, col));
            }
        }

        // Captures
        for (int dc = -1; dc <= 1; dc += 2) {
            int newRow = row + direction, newCol = col + dc;
            if (isValidPosition(newRow, newCol) && 
                board[newRow][newCol].type != EMPTY && 
                board[newRow][newCol].color != color) {
                if (newRow == promotionRow) {
                    moves.push_back(Move(row, col, newRow, newCol, QUEEN));
                } else {
                    moves.push_back(Move(row, col, newRow, newCol));
                }
            }
        }
    }

    void addSlidingMoves(vector<Move>& moves, int row, int col, int numDirs, const int* directions) const {
        Color color = board[row][col].color;
        
        for (int d = 0; d < numDirs; d++) {
            int dr = directions[d * 2];
            int dc = directions[d * 2 + 1];
            int r = row + dr;
            int c = col + dc;
            
            while (isValidPosition(r, c)) {
                if (board[r][c].type == EMPTY) {
                    moves.push_back(Move(row, col, r, c));
                } else {
                    if (board[r][c].color != color) {
                        moves.push_back(Move(row, col, r, c));
                    }
                    break;
                }
                r += dr;
                c += dc;
            }
        }
    }

    void addKnightMoves(vector<Move>& moves, int row, int col) const {
        Color color = board[row][col].color;
        int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        
        for (int i = 0; i < 8; i++) {
            int newRow = row + knightMoves[i][0];
            int newCol = col + knightMoves[i][1];
            if (isValidPosition(newRow, newCol) && 
                (board[newRow][newCol].type == EMPTY || board[newRow][newCol].color != color)) {
                moves.push_back(Move(row, col, newRow, newCol));
            }
        }
    }

    void addKingMoves(vector<Move>& moves, int row, int col) const {
        Color color = board[row][col].color;
        
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                int newRow = row + dr;
                int newCol = col + dc;
                if (isValidPosition(newRow, newCol) && 
                    (board[newRow][newCol].type == EMPTY || board[newRow][newCol].color != color)) {
                    moves.push_back(Move(row, col, newRow, newCol));
                }
            }
        }
    }

    bool isLegalMove(const Move& move) const {
        // Make a copy and try the move
        ChessBoard temp = *this;
        temp.makeMove(move);
        return !temp.isInCheck(currentTurn);
    }

    void makeMove(const Move& move) {
        Piece movingPiece = board[move.fromRow][move.fromCol];
        
        setPiece(move.toRow, move.toCol, movingPiece);
        setPiece(move.fromRow, move.fromCol, Piece(EMPTY, NONE));
        
        // Handle promotion
        if (move.promotion != EMPTY) {
            setPiece(move.toRow, move.toCol, Piece(move.promotion, movingPiece.color));
        }
        
        switchTurn();
    }

    void undoMove(const Move& move, const Piece& capturedPiece) {
        Piece movingPiece = board[move.toRow][move.toCol];
        
        // Handle promotion undo
        if (move.promotion != EMPTY) {
            movingPiece = Piece(PAWN, movingPiece.color);
        }
        
        setPiece(move.fromRow, move.fromCol, movingPiece);
        setPiece(move.toRow, move.toCol, capturedPiece);
        
        switchTurn();
    }

    bool isGameOver() const {
        return getLegalMoves().empty();
    }

    bool isCheckmate() const {
        return isGameOver() && isInCheck(currentTurn);
    }

    bool isStalemate() const {
        return isGameOver() && !isInCheck(currentTurn);
    }

    // Evaluation functions
    int getPieceSquareValue(const Piece& piece, int row, int col, bool isEndgame) const {
        if (piece.type == EMPTY) return 0;
        
        int squareIndex = row * 8 + col;
        if (piece.color == BLACK) {
            squareIndex = 63 - squareIndex;  // Flip for black
        }
        
        switch (piece.type) {
            case PAWN: return PAWN_TABLE[squareIndex];
            case KNIGHT: return KNIGHT_TABLE[squareIndex];
            case BISHOP: return BISHOP_TABLE[squareIndex];
            case ROOK: return ROOK_TABLE[squareIndex];
            case QUEEN: return QUEEN_TABLE[squareIndex];
            case KING: 
                return isEndgame ? KING_TABLE_ENDGAME[squareIndex] : KING_TABLE_MIDDLEGAME[squareIndex];
            default: return 0;
        }
    }

    bool isEndgame() const {
        int queens = 0, minors = 0;
        
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                PieceType type = board[r][c].type;
                if (type == QUEEN) queens++;
                if (type == BISHOP || type == KNIGHT) minors++;
            }
        }
        
        return queens == 0 || (queens == 2 && minors <= 2);
    }

    int evaluateBoard() const {
        if (isCheckmate()) {
            return (currentTurn == WHITE) ? -9999 : 9999;
        }
        if (isStalemate()) return 0;
        
        int values[7] = {0, 100, 500, 320, 330, 900, 20000}; // EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
        
        int score = 0;
        bool endgame = isEndgame();
        
        // Material and positional evaluation
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                Piece piece = board[r][c];
                if (piece.type != EMPTY) {
                    int pieceValue = values[piece.type];
                    int positionalValue = getPieceSquareValue(piece, r, c, endgame);
                    
                    if (piece.color == WHITE) {
                        score += pieceValue + positionalValue;
                    } else {
                        score -= pieceValue + positionalValue;
                    }
                }
            }
        }
        
        // Mobility bonus
        vector<Move> currentMoves = getLegalMoves();
        int mobility = currentMoves.size();
        if (currentTurn == WHITE) {
            score += mobility * 10;
        } else {
            score -= mobility * 10;
        }
        
        // Basic pawn structure evaluation
        for (int col = 0; col < BOARD_SIZE; col++) {
            int whitePawns = 0, blackPawns = 0;
            for (int row = 0; row < BOARD_SIZE; row++) {
                if (board[row][col].type == PAWN) {
                    if (board[row][col].color == WHITE) whitePawns++;
                    else blackPawns++;
                }
            }
            // Doubled pawns penalty
            if (whitePawns > 1) score -= 20 * (whitePawns - 1);
            if (blackPawns > 1) score += 20 * (blackPawns - 1);
        }
        
        return score;
    }

    // Alpha-Beta Pruning implementation
    int alphaBeta(int depth, int alpha, int beta, bool isMaximizing) {
        if (depth == 0 || isGameOver()) {
            return evaluateBoard();
        }

        if (isMaximizing) {
            int bestScore = -INF;
            vector<Move> moves = getLegalMoves();
            
            for (size_t i = 0; i < moves.size(); i++) {
                Piece captured = board[moves[i].toRow][moves[i].toCol];
                makeMove(moves[i]);
                int score = alphaBeta(depth - 1, alpha, beta, false);
                undoMove(moves[i], captured);
                
                bestScore = max(score, bestScore);
                alpha = max(alpha, score);
                
                // Beta cutoff - prune remaining branches
                if (beta <= alpha) {
                    break;  // Alpha-beta pruning
                }
            }
            return bestScore;
        } else {
            int bestScore = INF;
            vector<Move> moves = getLegalMoves();
            
            for (size_t i = 0; i < moves.size(); i++) {
                Piece captured = board[moves[i].toRow][moves[i].toCol];
                makeMove(moves[i]);
                int score = alphaBeta(depth - 1, alpha, beta, true);
                undoMove(moves[i], captured);
                
                bestScore = min(score, bestScore);
                beta = min(beta, score);
                
                // Alpha cutoff - prune remaining branches
                if (beta <= alpha) {
                    break;  // Alpha-beta pruning
                }
            }
            return bestScore;
        }
    }

    Move getAIMove(int depth) {
        vector<Move> moves = getLegalMoves();
        if (moves.empty()) return Move();
        
        Move bestMove;
        int bestScore = INF;  // AI plays as black (minimizing)
        vector<Move> goodMoves;
        int alpha = -INF;
        int beta = INF;
        
        for (size_t i = 0; i < moves.size(); i++) {
            Piece captured = board[moves[i].toRow][moves[i].toCol];
            makeMove(moves[i]);
            int score = alphaBeta(depth - 1, alpha, beta, true);
            undoMove(moves[i], captured);
            
            if (score < bestScore) {
                bestScore = score;
                goodMoves.clear();
                goodMoves.push_back(moves[i]);
            } else if (score == bestScore) {
                goodMoves.push_back(moves[i]);
            }
            
            // Update beta for root level
            beta = min(beta, score);
        }
        
        // Choose randomly among best moves
        if (!goodMoves.empty()) {
            bestMove = goodMoves[rand() % goodMoves.size()];
        }
        
        return bestMove;
    }

    Move parseMove(const string& input) const {
        if (input.length() < 4) return Move();
        
        int fromCol = input[0] - 'a';
        int fromRow = 8 - (input[1] - '0');
        int toCol = input[2] - 'a';
        int toRow = 8 - (input[3] - '0');
        
        if (!isValidPosition(fromRow, fromCol) || !isValidPosition(toRow, toCol)) {
            return Move();
        }
        
        Move move(fromRow, fromCol, toRow, toCol);
        
        // Handle pawn promotion
        Piece piece = getPiece(fromRow, fromCol);
        if (piece.type == PAWN) {
            if ((piece.color == WHITE && toRow == 0) || (piece.color == BLACK && toRow == 7)) {
                move.promotion = QUEEN;
            }
        }
        
        return move;
    }

    bool isMoveValid(const Move& move) const {
        vector<Move> legalMoves = getLegalMoves();
        for (size_t i = 0; i < legalMoves.size(); i++) {
            if (move.equals(legalMoves[i])) return true;
        }
        return false;
    }
};

int main() {
    ChessBoard board;
    Color humanColor = WHITE;
    
    cout << "=== CONSOLE CHESS AI WITH ALPHA-BETA PRUNING ===" << endl;
    cout << "You are White (♔ ♕ ♖ ♗ ♘ ♙)" << endl;
    cout << "AI is Black (♚ ♛ ♜ ♝ ♞ ♟)" << endl;
    cout << "Enter moves like: e2e4 (from e2 to e4)" << endl;

    while (!board.isGameOver()) {
        board.displayBoard();
        
        if (board.getCurrentTurn() == humanColor) {
            cout << "Your move (e.g. e2e4): ";
            string input;
            cin >> input;
            
            Move move = board.parseMove(input);
            if (move.fromRow != -1 && board.isMoveValid(move)) {
                board.makeMove(move);
                cout << "You played: " << move.toString() << endl;
            } else {
                cout << "Invalid move! Try again." << endl;
            }
        } else {
            cout << "AI is thinking..." << endl;
            Move aiMove = board.getAIMove(6);  // Increased depth due to alpha-beta efficiency
            if (aiMove.fromRow != -1) {
                cout << "AI plays: " << aiMove.toString() << endl;
                board.makeMove(aiMove);
            }
        }
    }
    
    board.displayBoard();
    
    if (board.isCheckmate()) {
        Color winner = (board.getCurrentTurn() == WHITE) ? BLACK : WHITE;
        cout << "Checkmate! " << (winner == WHITE ? "White" : "Black") << " wins!" << endl;
    } else if (board.isStalemate()) {
        cout << "Stalemate! It's a draw!" << endl;
    }
    
    return 0;
}