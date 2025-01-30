#include "gameState.h"
#include <stdexcept>
#include <iostream>

// Initialize game state at the starting position
void GameState::initialize() {
    initialize(STARTING_FEN);  // Use default chess starting position
}

void GameState::initialize(const std::string& fen) {
    board.initialize(fen);
    sideToMove = (fen.find(" w ") != std::string::npos) ? WHITE : BLACK;

    // Parse castling rights from FEN
    castlingRights = 0;
    if (fen.find("K") != std::string::npos) castlingRights |= WHITE_OO;
    if (fen.find("Q") != std::string::npos) castlingRights |= WHITE_OOO;
    if (fen.find("k") != std::string::npos) castlingRights |= BLACK_OO;
    if (fen.find("q") != std::string::npos) castlingRights |= BLACK_OOO;

    // Parse en passant square
    size_t enPassantStart = fen.find(" ", fen.find(" ") + 1); // Locate second space (start of en passant)
    if (enPassantStart != std::string::npos) {
        enPassantStart++; // Move to actual en passant field
        std::string enPassantField = fen.substr(enPassantStart, 2);
        if (enPassantField != "-") {
            try {
                enPassantSquare = algebraicToSquare(enPassantField);
            } catch (const std::invalid_argument&) {
                std::cerr << "Warning: Invalid en passant field in FEN: " << enPassantField << std::endl;
                enPassantSquare = -1;
            }
        } else {
            enPassantSquare = -1;
        }
    } else {
        enPassantSquare = -1;
    }

    moveHistory.clear();
}


// Make move and update game state
void GameState::makeMove(const Move& move) {
    Move& moveWithHistory = const_cast<Move&>(move);
    moveWithHistory.previousCastlingRights = castlingRights;
    moveWithHistory.previousEnPassantSquare = enPassantSquare;
    
    // Check for pawn promotion
    bool isWhite = (sideToMove == WHITE);
    bool isPawn = (move.piece == 'P' || move.piece == 'p');
    bool isPromotionRank = (isWhite && move.destinationSquare >= 56) || (!isWhite && move.destinationSquare <= 7);

    if (isPawn && isPromotionRank) {
        // If no promotion piece is specified, promote to queen by default
        moveWithHistory.promotionPiece = (move.promotionPiece != '\0') ? move.promotionPiece : (isWhite ? 'Q' : 'q');
    }

    // Make the move on the board
    board.makeMove(move);

    // Handle promotion by replacing the pawn with the promoted piece
    if (isPawn && isPromotionRank) {
        board.pawns &= ~(1ULL << move.destinationSquare); // Remove the pawn
        if (moveWithHistory.promotionPiece == 'Q' || moveWithHistory.promotionPiece == 'q') {
            board.queens |= (1ULL << move.destinationSquare);
        } else if (moveWithHistory.promotionPiece == 'R' || moveWithHistory.promotionPiece == 'r') {
            board.rooks |= (1ULL << move.destinationSquare);
        } else if (moveWithHistory.promotionPiece == 'B' || moveWithHistory.promotionPiece == 'b') {
            board.bishops |= (1ULL << move.destinationSquare);
        } else if (moveWithHistory.promotionPiece == 'N' || moveWithHistory.promotionPiece == 'n') {
            board.knights |= (1ULL << move.destinationSquare);
        }
    }
    
    // Update game state
    sideToMove = (sideToMove == WHITE) ? BLACK : WHITE;
    updateCastlingRights(move);
    updateEnPassantSquare(move);

    // Add to history after all state is updated
    moveHistory.push_back(move);
}

// Undo move and update game state
void GameState::undoMove() {
    if (!moveHistory.empty()) {
        Move lastMove = moveHistory.back();
        moveHistory.pop_back();
        
        // Undo the move on the board
        board.undoMove(lastMove);

        // If it was a promotion, put the pawn back
        if (lastMove.promotionPiece != '\0') {
            board.queens &= ~(1ULL << lastMove.destinationSquare);
            board.rooks &= ~(1ULL << lastMove.destinationSquare);
            board.bishops &= ~(1ULL << lastMove.destinationSquare);
            board.knights &= ~(1ULL << lastMove.destinationSquare);
            board.pawns |= (1ULL << lastMove.destinationSquare);
        }
        
        // Restore exact previous state
        sideToMove = (sideToMove == WHITE) ? BLACK : WHITE;
        castlingRights = lastMove.previousCastlingRights;
        enPassantSquare = lastMove.previousEnPassantSquare;
    }
}

// Update who has what castling rights
void GameState::updateCastlingRights(const Move& move) {
    // Remove castling rights if king moves
    if (move.piece == 'K') {
        if (sideToMove == WHITE) {
            castlingRights &= ~(WHITE_OO | WHITE_OOO);
        } else {
            castlingRights &= ~(BLACK_OO | BLACK_OOO);
        }
    }
    
    // Remove castling rights if rook moves or is captured
    if (move.piece == 'R' || move.piece == 'r' || (board.getPiece(move.destinationSquare)) == 'R' || (board.getPiece(move.destinationSquare) == 'r')) {
        // Check source and destination squares for rook positions
        if (move.sourceSquare == 56 || move.destinationSquare == 56) { // a1
            castlingRights &= ~WHITE_OOO;
        }
        if (move.sourceSquare == 63 || move.destinationSquare == 63) { // h1
            castlingRights &= ~WHITE_OO;
        }
        if (move.sourceSquare == 0 || move.destinationSquare == 0) { // a8
            castlingRights &= ~BLACK_OOO;
        }
        if (move.sourceSquare == 7 || move.destinationSquare == 7) { // h8
            castlingRights &= ~BLACK_OO;
        }
    }
}

// Update possible en passant square
void GameState::updateEnPassantSquare(const Move& move) {
    // Set en passant square only for pawn double moves
    if (move.piece == 'P' || move.piece == 'p') {
        int rankMove = move.destinationSquare / 8 - move.sourceSquare / 8;
        if (abs(rankMove) == 2) {
            // Set en passant square to the square behind the pawn
            enPassantSquare = (move.sourceSquare + move.destinationSquare) / 2;
        } else {
            enPassantSquare = -1;
        }
    } else {
        enPassantSquare = -1;
    }
}

// Restore previous castling rights during moveUndo
void GameState::updateCastlingRightsUndo(const Move& move) {
    castlingRights = move.previousCastlingRights;
}

// Restore previous EnPassantSquare during moveUndo
void GameState::updateEnPassantSquareUndo(const Move& move) {
    enPassantSquare = move.previousEnPassantSquare;
}

bool testEvaluation() {
    GameState gs;
    gs.initialize();  // Start from default position

    int eval = evaluate(gs.board);
    std::cout << "Evaluation score (initial position): " << eval << std::endl;

    // Move a white pawn forward
    Move e2e4('P', algebraicToSquare("e2"), algebraicToSquare("e4"));
    gs.makeMove(e2e4);
    eval = evaluate(gs.board);
    std::cout << "After 1. e4: " << eval << std::endl;

    return true;
}