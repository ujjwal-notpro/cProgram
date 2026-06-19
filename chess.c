#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Chess piece definitions
#define EMPTY   '.'
#define W_KING  'K'
#define W_QUEEN 'Q'
#define W_ROOK  'R'
#define W_BISHOP 'B'
#define W_KNIGHT 'N'
#define W_PAWN  'P'
#define B_KING  'k'
#define B_QUEEN 'q'
#define B_ROOK  'r'
#define B_BISHOP 'b'
#define B_KNIGHT 'n'
#define B_PAWN  'p'

// Board structure
typedef struct {
    char board[8][8];
    bool white_to_move;
    bool white_king_moved;
    bool black_king_moved;
    bool white_rook_a_moved;
    bool white_rook_h_moved;
    bool black_rook_a_moved;
    bool black_rook_h_moved;
} ChessGame;

// Function prototypes
void initialize_board(ChessGame *game);
void print_board(ChessGame *game);
bool is_valid_position(int row, int col);
bool is_white_piece(char piece);
bool is_black_piece(char piece);
bool is_valid_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col);
bool is_path_clear(ChessGame *game, int from_row, int from_col, int to_row, int to_col);
bool validate_pawn_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col);
bool validate_knight_move(int from_row, int from_col, int to_row, int to_col);
bool validate_bishop_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col);
bool validate_rook_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col);
bool validate_queen_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col);
bool validate_king_move(int from_row, int from_col, int to_row, int to_col);
bool make_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col);
void parse_move(char *move, int *from_row, int *from_col, int *to_row, int *to_col);

// Initialize the chess board with starting position
void initialize_board(ChessGame *game) {
    // Black pieces
    game->board[0][0] = B_ROOK;
    game->board[0][1] = B_KNIGHT;
    game->board[0][2] = B_BISHOP;
    game->board[0][3] = B_QUEEN;
    game->board[0][4] = B_KING;
    game->board[0][5] = B_BISHOP;
    game->board[0][6] = B_KNIGHT;
    game->board[0][7] = B_ROOK;
    
    // Black pawns
    for (int i = 0; i < 8; i++) {
        game->board[1][i] = B_PAWN;
    }
    
    // Empty squares
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            game->board[i][j] = EMPTY;
        }
    }
    
    // White pawns
    for (int i = 0; i < 8; i++) {
        game->board[6][i] = W_PAWN;
    }
    
    // White pieces
    game->board[7][0] = W_ROOK;
    game->board[7][1] = W_KNIGHT;
    game->board[7][2] = W_BISHOP;
    game->board[7][3] = W_QUEEN;
    game->board[7][4] = W_KING;
    game->board[7][5] = W_BISHOP;
    game->board[7][6] = W_KNIGHT;
    game->board[7][7] = W_ROOK;
    
    game->white_to_move = true;
    game->white_king_moved = false;
    game->black_king_moved = false;
    game->white_rook_a_moved = false;
    game->white_rook_h_moved = false;
    game->black_rook_a_moved = false;
    game->black_rook_h_moved = false;
}

// Print the chess board
void print_board(ChessGame *game) {
    printf("\n  a b c d e f g h\n");
    printf("  ---------------\n");
    for (int i = 0; i < 8; i++) {
        printf("%d|", 8 - i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", game->board[i][j]);
        }
        printf("|%d\n", 8 - i);
    }
    printf("  ---------------\n");
    printf("  a b c d e f g h\n\n");
    printf("Turn: %s\n", game->white_to_move ? "White" : "Black");
}

// Check if position is valid
bool is_valid_position(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

// Check if piece is white
bool is_white_piece(char piece) {
    return piece >= 'A' && piece <= 'Z';
}

// Check if piece is black
bool is_black_piece(char piece) {
    return piece >= 'a' && piece <= 'z';
}

// Check if path is clear (for sliding pieces)
bool is_path_clear(ChessGame *game, int from_row, int from_col, int to_row, int to_col) {
    int row_dir = (to_row > from_row) ? 1 : (to_row < from_row) ? -1 : 0;
    int col_dir = (to_col > from_col) ? 1 : (to_col < from_col) ? -1 : 0;
    
    int curr_row = from_row + row_dir;
    int curr_col = from_col + col_dir;
    
    while (curr_row != to_row || curr_col != to_col) {
        if (game->board[curr_row][curr_col] != EMPTY) {
            return false;
        }
        curr_row += row_dir;
        curr_col += col_dir;
    }
    
    return true;
}

// Validate pawn move
bool validate_pawn_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col) {
    char piece = game->board[from_row][from_col];
    int direction = is_white_piece(piece) ? -1 : 1;
    
    // Move forward one square
    if (to_col == from_col && to_row == from_row + direction && 
        game->board[to_row][to_col] == EMPTY) {
        return true;
    }
    
    // Move forward two squares from starting position
    int start_row = is_white_piece(piece) ? 6 : 1;
    if (from_row == start_row && to_col == from_col && 
        to_row == from_row + 2 * direction &&
        game->board[to_row][to_col] == EMPTY &&
        game->board[from_row + direction][from_col] == EMPTY) {
        return true;
    }
    
    // Capture diagonally
    if (abs(to_col - from_col) == 1 && to_row == from_row + direction) {
        char target = game->board[to_row][to_col];
        if ((is_white_piece(piece) && is_black_piece(target)) ||
            (is_black_piece(piece) && is_white_piece(target))) {
            return true;
        }
    }
    
    return false;
}

// Validate knight move
bool validate_knight_move(int from_row, int from_col, int to_row, int to_col) {
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);
    
    return (row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2);
}

// Validate bishop move
bool validate_bishop_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col) {
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);
    
    if (row_diff != col_diff) {
        return false;
    }
    
    return is_path_clear(game, from_row, from_col, to_row, to_col);
}

// Validate rook move
bool validate_rook_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col) {
    if (from_row != to_row && from_col != to_col) {
        return false;
    }
    
    return is_path_clear(game, from_row, from_col, to_row, to_col);
}

// Validate queen move
bool validate_queen_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col) {
    return validate_rook_move(game, from_row, from_col, to_row, to_col) ||
           validate_bishop_move(game, from_row, from_col, to_row, to_col);
}

// Validate king move
bool validate_king_move(int from_row, int from_col, int to_row, int to_col) {
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);
    
    return row_diff <= 1 && col_diff <= 1 && (row_diff + col_diff > 0);
}

// Check if a move is valid
bool is_valid_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col) {
    // Check positions are valid
    if (!is_valid_position(from_row, from_col) || !is_valid_position(to_row, to_col)) {
        return false;
    }
    
    char piece = game->board[from_row][from_col];
    char target = game->board[to_row][to_col];
    
    // Check if there's a piece to move
    if (piece == EMPTY) {
        printf("No piece at source position!\n");
        return false;
    }
    
    // Check if correct player is moving
    if ((game->white_to_move && !is_white_piece(piece)) ||
        (!game->white_to_move && !is_black_piece(piece))) {
        printf("Wrong player's turn!\n");
        return false;
    }
    
    // Check if capturing own piece
    if ((is_white_piece(piece) && is_white_piece(target)) ||
        (is_black_piece(piece) && is_black_piece(target))) {
        printf("Cannot capture your own piece!\n");
        return false;
    }
    
    // Validate move based on piece type
    char piece_type = toupper(piece);
    bool valid = false;
    
    switch (piece_type) {
        case 'P':
            valid = validate_pawn_move(game, from_row, from_col, to_row, to_col);
            break;
        case 'N':
            valid = validate_knight_move(from_row, from_col, to_row, to_col);
            break;
        case 'B':
            valid = validate_bishop_move(game, from_row, from_col, to_row, to_col);
            break;
        case 'R':
            valid = validate_rook_move(game, from_row, from_col, to_row, to_col);
            break;
        case 'Q':
            valid = validate_queen_move(game, from_row, from_col, to_row, to_col);
            break;
        case 'K':
            valid = validate_king_move(from_row, from_col, to_row, to_col);
            break;
        default:
            valid = false;
    }
    
    if (!valid) {
        printf("Invalid move for this piece!\n");
    }
    
    return valid;
}

// Make a move on the board
bool make_move(ChessGame *game, int from_row, int from_col, int to_row, int to_col) {
    if (!is_valid_move(game, from_row, from_col, to_row, to_col)) {
        return false;
    }
    
    char piece = game->board[from_row][from_col];
    
    // Update castling flags
    if (piece == W_KING) game->white_king_moved = true;
    if (piece == B_KING) game->black_king_moved = true;
    if (piece == W_ROOK && from_row == 7 && from_col == 0) game->white_rook_a_moved = true;
    if (piece == W_ROOK && from_row == 7 && from_col == 7) game->white_rook_h_moved = true;
    if (piece == B_ROOK && from_row == 0 && from_col == 0) game->black_rook_a_moved = true;
    if (piece == B_ROOK && from_row == 0 && from_col == 7) game->black_rook_h_moved = true;
    
    // Make the move
    game->board[to_row][to_col] = piece;
    game->board[from_row][from_col] = EMPTY;
    
    // Pawn promotion (simplified - always promote to queen)
    if ((piece == W_PAWN && to_row == 0) || (piece == B_PAWN && to_row == 7)) {
        game->board[to_row][to_col] = is_white_piece(piece) ? W_QUEEN : B_QUEEN;
        printf("Pawn promoted to Queen!\n");
    }
    
    // Switch turns
    game->white_to_move = !game->white_to_move;
    
    return true;
}

// Parse move in algebraic notation (e.g., "e2e4")
void parse_move(char *move, int *from_row, int *from_col, int *to_row, int *to_col) {
    *from_col = move[0] - 'a';
    *from_row = 8 - (move[1] - '0');
    *to_col = move[2] - 'a';
    *to_row = 8 - (move[3] - '0');
}

// Main function
int main() {
    ChessGame game;
    char move[10];
    int from_row, from_col, to_row, to_col;
    
    initialize_board(&game);
    
    printf("Chess Game - Move format: e2e4 (from square to square)\n");
    printf("Type 'quit' to exit\n");
    
    while (1) {
        print_board(&game);
        
        printf("Enter move: ");
        if (scanf("%s", move) != 1) {
            break;
        }
        
        if (strcmp(move, "quit") == 0) {
            printf("Thanks for playing!\n");
            break;
        }
        
        if (strlen(move) != 4) {
            printf("Invalid move format! Use format like 'e2e4'\n");
            continue;
        }
        
        parse_move(move, &from_row, &from_col, &to_row, &to_col);
        
        if (make_move(&game, from_row, from_col, to_row, to_col)) {
            printf("Move successful!\n");
        } else {
            printf("Invalid move! Try again.\n");
        }
    }
    
    return 0;
}