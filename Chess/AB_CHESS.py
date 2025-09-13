import pygame
import chess
import math
import random

# Initialize pygame
pygame.init()
WIDTH, HEIGHT = 640, 640
SQUARE_SIZE = WIDTH // 8
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Chess AI vs User (Improved Minimax)")

# Font for piece symbols
font = pygame.font.SysFont("Segoe UI Symbol", 48)

piece_symbols = {
    "P": "♙", "R": "♖", "N": "♘", "B": "♗", "Q": "♕", "K": "♔",
    "p": "♟", "r": "♜", "n": "♞", "b": "♝", "q": "♛", "k": "♚"
}

# Piece-square tables for positional evaluation
PAWN_TABLE = [
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
]

KNIGHT_TABLE = [
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
]

BISHOP_TABLE = [
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
]

ROOK_TABLE = [
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    0,  0,  0,  5,  5,  0,  0,  0
]

QUEEN_TABLE = [
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
    0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
]

KING_TABLE_MIDDLEGAME = [
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
]

KING_TABLE_ENDGAME = [
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50
]

# Draw chessboard
def draw_board():
    colors = [pygame.Color("white"), pygame.Color("gray")]
    for r in range(8):
        for c in range(8):
            color = colors[(r + c) % 2]
            pygame.draw.rect(screen, color,
                             pygame.Rect(c*SQUARE_SIZE, r*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

# Highlight selected square and moves
def highlight_squares(board, selected_square):
    if selected_square is not None:
        # Highlight selected square in blue
        col, row = chess.square_file(selected_square), 7 - chess.square_rank(selected_square)
        pygame.draw.rect(screen, pygame.Color("blue"),
                         pygame.Rect(col*SQUARE_SIZE, row*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 4)

        # Highlight legal moves in green
        for move in board.legal_moves:
            if move.from_square == selected_square:
                col, row = chess.square_file(move.to_square), 7 - chess.square_rank(move.to_square)
                pygame.draw.rect(screen, pygame.Color("green"),
                                 pygame.Rect(col*SQUARE_SIZE, row*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 4)

# Draw pieces on the board
def draw_pieces(board):
    for r in range(8):
        for c in range(8):
            square = chess.square(c, 7-r)
            piece = board.piece_at(square)
            if piece:
                piece_str = piece.symbol()
                symbol = piece_symbols[piece_str]
                text_surface = font.render(symbol, True, (0, 0, 0))
                text_rect = text_surface.get_rect(center=(c*SQUARE_SIZE + SQUARE_SIZE//2,
                                                          r*SQUARE_SIZE + SQUARE_SIZE//2))
                screen.blit(text_surface, text_rect)

def get_piece_square_value(piece, square, is_endgame=False):
    """Get positional value for a piece on a specific square"""
    piece_type = piece.piece_type
    color = piece.color
    
    # Convert square to array index (0-63)
    square_index = square
    if color == chess.BLACK:
        # Flip the square for black pieces
        square_index = 63 - square
    
    if piece_type == chess.PAWN:
        return PAWN_TABLE[square_index]
    elif piece_type == chess.KNIGHT:
        return KNIGHT_TABLE[square_index]
    elif piece_type == chess.BISHOP:
        return BISHOP_TABLE[square_index]
    elif piece_type == chess.ROOK:
        return ROOK_TABLE[square_index]
    elif piece_type == chess.QUEEN:
        return QUEEN_TABLE[square_index]
    elif piece_type == chess.KING:
        if is_endgame:
            return KING_TABLE_ENDGAME[square_index]
        else:
            return KING_TABLE_MIDDLEGAME[square_index]
    
    return 0

def is_endgame(board):
    """Simple endgame detection"""
    # Count material
    queens = len(board.pieces(chess.QUEEN, chess.WHITE)) + len(board.pieces(chess.QUEEN, chess.BLACK))
    minors = (len(board.pieces(chess.BISHOP, chess.WHITE)) + len(board.pieces(chess.BISHOP, chess.BLACK)) +
              len(board.pieces(chess.KNIGHT, chess.WHITE)) + len(board.pieces(chess.KNIGHT, chess.BLACK)))
    
    # Endgame if no queens or very few pieces
    return queens == 0 or (queens == 2 and minors <= 2)

# Improved evaluation function
def evaluate_board(board):
    if board.is_checkmate():
        return -9999 if board.turn == chess.WHITE else 9999
    if board.is_stalemate() or board.is_insufficient_material():
        return 0
    
    # Piece values
    values = {
        chess.PAWN: 100, chess.KNIGHT: 320, chess.BISHOP: 330,
        chess.ROOK: 500, chess.QUEEN: 900, chess.KING: 20000
    }
    
    score = 0
    endgame = is_endgame(board)
    
    # Material and positional evaluation
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece:
            piece_value = values[piece.piece_type]
            positional_value = get_piece_square_value(piece, square, endgame)
            
            if piece.color == chess.WHITE:
                score += piece_value + positional_value
            else:
                score -= piece_value + positional_value
    
    # Additional positional factors
    
    # Mobility (number of legal moves)
    white_mobility = len(list(board.legal_moves)) if board.turn == chess.WHITE else 0
    board.push(chess.Move.null()) if board.turn == chess.WHITE else None
    black_mobility = len(list(board.legal_moves)) if board.turn == chess.BLACK else 0
    if board.turn == chess.BLACK:
        board.pop()
    
    score += (white_mobility - black_mobility) * 10
    
    # King safety
    white_king_square = board.king(chess.WHITE)
    black_king_square = board.king(chess.BLACK)
    
    if white_king_square and not endgame:
        # Penalize exposed king in middlegame
        if chess.square_file(white_king_square) in [3, 4]:  # King in center
            score -= 50
    
    if black_king_square and not endgame:
        if chess.square_file(black_king_square) in [3, 4]:
            score += 50
    
    # Pawn structure bonuses
    white_pawns = board.pieces(chess.PAWN, chess.WHITE)
    black_pawns = board.pieces(chess.PAWN, chess.BLACK)
    
    # Doubled pawns penalty
    for file in range(8):
        file_squares = [chess.square(file, rank) for rank in range(8)]
        white_pawns_in_file = len([sq for sq in file_squares if sq in white_pawns])
        black_pawns_in_file = len([sq for sq in file_squares if sq in black_pawns])
        
        if white_pawns_in_file > 1:
            score -= 20 * (white_pawns_in_file - 1)
        if black_pawns_in_file > 1:
            score += 20 * (black_pawns_in_file - 1)
    
    # Passed pawns bonus
    for square in white_pawns:
        file = chess.square_file(square)
        rank = chess.square_rank(square)
        
        # Check if it's a passed pawn
        passed = True
        for check_rank in range(rank + 1, 8):
            for check_file in [file - 1, file, file + 1]:
                if 0 <= check_file <= 7:
                    check_square = chess.square(check_file, check_rank)
                    if check_square in black_pawns:
                        passed = False
                        break
            if not passed:
                break
        
        if passed:
            score += 20 * (rank - 1)  # More valuable as it advances
    
    return score

# Minimax with alpha-beta pruning
def minimax(board, depth, alpha, beta, is_maximizing):
    if depth == 0 or board.is_game_over():
        return evaluate_board(board)

    if is_maximizing:
        best_score = -math.inf
        # Order moves (captures first, then others)
        moves = list(board.legal_moves)
        moves.sort(key=lambda move: board.piece_at(move.to_square) is not None, reverse=True)
        
        for move in moves:
            board.push(move)
            score = minimax(board, depth-1, alpha, beta, False)
            board.pop()
            best_score = max(score, best_score)
            alpha = max(alpha, best_score)
            if beta <= alpha:
                break  # Alpha-beta cutoff
        return best_score
    else:
        best_score = math.inf
        moves = list(board.legal_moves)
        moves.sort(key=lambda move: board.piece_at(move.to_square) is not None, reverse=True)
        
        for move in moves:
            board.push(move)
            score = minimax(board, depth-1, alpha, beta, True)
            board.pop()
            best_score = min(score, best_score)
            beta = min(beta, best_score)
            if beta <= alpha:
                break  # Alpha-beta cutoff
        return best_score

# AI move using minimax with alpha-beta pruning
def ai_move(board, depth=3):
    best_move = None
    best_score = math.inf  # AI plays as black (minimizing)
    
    # Get all legal moves and sort them (captures first)
    moves = list(board.legal_moves)
    moves.sort(key=lambda move: board.piece_at(move.to_square) is not None, reverse=True)
    
    # Add some randomness among equally good moves
    good_moves = []
    
    for move in moves:
        board.push(move)
        score = minimax(board, depth-1, -math.inf, math.inf, True)
        board.pop()
        
        if score < best_score:
            best_score = score
            good_moves = [move]
        elif score == best_score:
            good_moves.append(move)
    
    # Choose randomly among best moves to add variety
    if good_moves:
        best_move = random.choice(good_moves)
    
    return best_move

def main():
    board = chess.Board()
    running = True
    selected_square = None
    user_color = chess.WHITE  # user plays White
    clock = pygame.time.Clock()

    print("Chess AI vs User")
    print("You are playing as White (bottom). Click to select and move pieces.")
    print("AI difficulty: Depth 3 with improved evaluation")

    while running:
        draw_board()
        highlight_squares(board, selected_square)
        draw_pieces(board)
        pygame.display.flip()

        # Check for game over
        if board.is_game_over():
            if board.is_checkmate():
                winner = "White" if board.turn == chess.BLACK else "Black"
                print(f"Checkmate! {winner} wins!")
            elif board.is_stalemate():
                print("Stalemate! It's a draw!")
            elif board.is_insufficient_material():
                print("Draw due to insufficient material!")
            else:
                print("Game over!")

        if board.turn != user_color and not board.is_game_over():  # AI's turn
            print("AI is thinking...")
            move = ai_move(board, depth=3)
            if move:
                print(f"AI plays: {move}")
                board.push(move)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            if board.turn == user_color and event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                col, row = x // SQUARE_SIZE, y // SQUARE_SIZE
                square = chess.square(col, 7-row)

                if selected_square is None:
                    if board.piece_at(square) and board.piece_at(square).color == user_color:
                        selected_square = square
                else:
                    move = chess.Move(selected_square, square)
                    # Handle promotion (automatically promote to queen)
                    if move.promotion is None and board.piece_at(selected_square).piece_type == chess.PAWN:
                        if (user_color == chess.WHITE and chess.square_rank(square) == 7) or \
                           (user_color == chess.BLACK and chess.square_rank(square) == 0):
                            move = chess.Move(selected_square, square, promotion=chess.QUEEN)
                    
                    if move in board.legal_moves:
                        print(f"You play: {move}")
                        board.push(move)
                    selected_square = None

        clock.tick(15)

    pygame.quit()

if __name__ == "__main__":
    main()