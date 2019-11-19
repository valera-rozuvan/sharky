#include <stdlib.h>

#include "board.h"
#include "fen.h"
#include "board_routines.h"
#include "bitboard.h"
#include "zobrist_hashing.h"

/*
 *
 * The below description of FEN is taken from Wikipedia:
 *
 *   https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 *
 * Forsyth–Edwards Notation (FEN) is a standard notation for describing a particular board position of a chess game.
 * The purpose of FEN is to provide all the necessary information to restart a game from a particular position.
 *
 * A FEN "record" defines a particular game position, all in one text line and using only the ASCII character set.
 *
 * A FEN record contains six fields. The separator between fields is a space. The fields are:
 *
 * 1. Piece placement (from White's perspective). Each rank is described, starting with rank 8 and ending with rank 1;
 *    within each rank, the contents of each square are described from file "a" through file "h". Following the
 *    Standard Algebraic Notation (SAN), each piece is identified by a single letter taken from the standard English
 *    names (pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K"). White pieces are
 *    designated using upper-case letters ("PNBRQK") while black pieces use lowercase ("pnbrqk"). Empty squares are
 *    noted using digits 1 through 8 (the number of empty squares), and "/" separates ranks.
 *
 * 2. Active color. "w" means White moves next, "b" means Black moves next.
 *
 * 3. Castling availability. If neither side can castle, this is "-". Otherwise, this has one or more
 *    letters: "K" (White can castle kingside), "Q" (White can castle queenside), "k" (Black can castle kingside),
 *    and/or "q" (Black can castle queenside).
 *
 * 4. En passant target square in algebraic notation. If there's no en passant target square, this is "-". If a pawn
 *    has just made a two-square move, this is the position "behind" the pawn. This is recorded regardless of whether
 *    there is a pawn in position to make an en passant capture.
 *
 * 5. Halfmove clock: This is the number of halfmoves since the last capture or pawn advance. This is used to determine
 *    if a draw can be claimed under the fifty-move rule.
 *
 * 6. Fullmove number: The number of the full move. It starts at 1, and is incremented after Black's move.
 *
 *
 * Examples:
 *
 * Here is the FEN for the starting position:
 *   rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
 *
 * Here is the FEN after the move 1. e4:
 *   rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
 *
 * And then after 1. ... c5:
 *   rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
 *
 * And then after 2. Nf3:
 *   rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2
 *
 */

const char *onlyAllowedFenSymbols = "abcdefgh012345678 /-PNBRQKpnbrqkwb";
const char *onlyChessPieceSymbols = "PNBRQKpnbrqk";
const char *onlyDigits1To8Symbols = "12345678";
const char *onlySideToMoveSymbols = "wb";
const char *onlyCastlingRightsSymbols = "KQkq";
const char *onlyFileSymbols = "abcdefgh";

unsigned char arrayContainsChar(const char *hayStack, char needle)
{
  unsigned short idx = 0;

  do {
    if (hayStack[idx] == needle) {
      return 1;
    }

    idx += 1;
  } while ((hayStack[idx] != '\0') && (idx < 1024));

  return 0;
}

unsigned char pieceCharToPiece(char pieceCharRepr)
{
  if (pieceCharRepr == 'P') return wP;
  if (pieceCharRepr == 'N') return wN;
  if (pieceCharRepr == 'B') return wB;
  if (pieceCharRepr == 'R') return wR;
  if (pieceCharRepr == 'Q') return wQ;
  if (pieceCharRepr == 'K') return wK;

  if (pieceCharRepr == 'p') return bP;
  if (pieceCharRepr == 'n') return bN;
  if (pieceCharRepr == 'b') return bB;
  if (pieceCharRepr == 'r') return bR;
  if (pieceCharRepr == 'q') return bQ;
  if (pieceCharRepr == 'k') return bK;

  return EMPTY;
}

unsigned char digit1To8CharToNum(char digitCharRepr)
{
  if (digitCharRepr == '1') return 1;
  if (digitCharRepr == '2') return 2;
  if (digitCharRepr == '3') return 3;
  if (digitCharRepr == '4') return 4;
  if (digitCharRepr == '5') return 5;
  if (digitCharRepr == '6') return 6;
  if (digitCharRepr == '7') return 7;

  return 8;
}

unsigned char fileCharToFile(char fileChar)
{
  if (fileChar == 'a') return FILE_A;
  if (fileChar == 'b') return FILE_B;
  if (fileChar == 'c') return FILE_C;
  if (fileChar == 'd') return FILE_D;
  if (fileChar == 'e') return FILE_E;
  if (fileChar == 'f') return FILE_F;
  if (fileChar == 'g') return FILE_G;

  return FILE_H;
}

unsigned char sideCharToSide(char sideCharRepr)
{
  if (sideCharRepr == 'w') return WHITE;

  return BLACK;
}

unsigned char castlingPermCharToCastlingPerm(char castlingPermChar)
{
  if (castlingPermChar == 'K') return WKCastling;
  if (castlingPermChar == 'Q') return WQCastling;
  if (castlingPermChar == 'k') return BKCastling;

  return BQCastling;
}

unsigned char setInitialPosReturnError(BOARD *cBoard, unsigned char errorCode)
{
  setupInitialPosition(cBoard);

  return errorCode;
}

unsigned char setPositionFromFen(BOARD *cBoard, const char *fenStr)
{
  unsigned char idx1 = 0;
  unsigned char idx2 = 0;
  unsigned char currentFile = 0;
  unsigned char currentRank = 0;
  unsigned char numOfEmpty = 0;

  if (fenStr == NULL) {
    return setInitialPosReturnError(cBoard, 99);
  }

  setupEmptyPosition(cBoard);

  for (idx1 = 0; idx1 <= MAX_ALLOWED_FEN_STRING_LENGTH; idx1 += 1) {
    if (fenStr[idx1] == '\0') {
      break;
    }
  }

  if ((idx1 == 0) || (idx1 > MAX_ALLOWED_FEN_STRING_LENGTH)) {
    return setInitialPosReturnError(cBoard, 1);
  }

  idx1 = 0;
  do {
    if (arrayContainsChar(onlyAllowedFenSymbols, fenStr[idx1]) == 0) {
      return setInitialPosReturnError(cBoard, 2);
    }

    idx1 += 1;
  } while (fenStr[idx1] != '\0');

  idx1 = 0;
  currentFile = FILE_A;
  currentRank = RANK_8;
  do {
    if (fenStr[idx1] == '\0') {
      return setInitialPosReturnError(cBoard, 3);
    } else if (fenStr[idx1] == '/') {
      if ((currentFile != FILE_H + 1) || (currentRank == RANK_1)) {
        return setInitialPosReturnError(cBoard, 4);
      }

      idx1 += 1;
      currentFile = FILE_A;
      currentRank -= 1;

      continue;
    }

    if (arrayContainsChar(onlyChessPieceSymbols, fenStr[idx1]) == 1) {
      cBoard->pieces[FileRankTo120SQ(currentFile, currentRank)] = pieceCharToPiece(fenStr[idx1]);
      currentFile += 1;
    } else if (arrayContainsChar(onlyDigits1To8Symbols, fenStr[idx1]) == 1) {
      numOfEmpty = digit1To8CharToNum(fenStr[idx1]);

      for (idx2 = 0; idx2 < numOfEmpty; idx2 += 1) {
        cBoard->pieces[FileRankTo120SQ(currentFile, currentRank)] = pieceCharToPiece(' ');
        currentFile += 1;
      }
    } else {
      return setInitialPosReturnError(cBoard, 5);
    }

    idx1 += 1;
  } while (fenStr[idx1] != ' ');

  if ((currentRank != RANK_1) || (currentFile != FILE_H + 1)) {
    return setInitialPosReturnError(cBoard, 6);
  }

  idx1 += 1;
  if (fenStr[idx1] == '\0') {
    return setInitialPosReturnError(cBoard, 7);
  }

  if (arrayContainsChar(onlySideToMoveSymbols, fenStr[idx1]) == 0) {
    return setInitialPosReturnError(cBoard, 8);
  }
  cBoard->side = sideCharToSide(fenStr[idx1]);

  idx1 += 1;
  if (fenStr[idx1] != ' ' || fenStr[idx1] == '\0') {
    return setInitialPosReturnError(cBoard, 9);
  }

  idx1 += 1;
  if (fenStr[idx1] == '-') {
    idx1 += 1;
  } else {
    do {
      if (fenStr[idx1] == '\0') {
        return setInitialPosReturnError(cBoard, 10);
      }

      if (arrayContainsChar(onlyCastlingRightsSymbols, fenStr[idx1]) == 1) {
        SET_BIT(cBoard->castlingPerm, castlingPermCharToCastlingPerm(fenStr[idx1]));
      } else {
        return setInitialPosReturnError(cBoard, 11);
      }

      idx1 += 1;
    } while (fenStr[idx1] != ' ');
  }

  if (fenStr[idx1] != ' ' || fenStr[idx1] == '\0') {
    return setInitialPosReturnError(cBoard, 12);
  }

  idx1 += 1;
  if (fenStr[idx1] == '-') {
    idx1 += 1;
  } else {
    if (fenStr[idx1] == '\0') {
      return setInitialPosReturnError(cBoard, 13);
    }

    if (arrayContainsChar(onlyFileSymbols, fenStr[idx1]) == 1) {
      cBoard->enPassantFile = fileCharToFile(fenStr[idx1]);
    } else {
      return setInitialPosReturnError(cBoard, 14);
    }

    idx1 += 1;
    if (fenStr[idx1] == '\0') {
      return setInitialPosReturnError(cBoard, 15);
    }

    if (arrayContainsChar(onlyDigits1To8Symbols, fenStr[idx1]) == 0) {
      return setInitialPosReturnError(cBoard, 16);
    }
  }

  idx1 += 1;

  if (fenStr[idx1] != '\0') {
    // TODO: Finish parsing FEN string. Properly set `fiftyMove`, and `historyPly`.

    cBoard->fiftyMove = 0;
    cBoard->historyPly = 0;
  }

  for (idx1 = 0; idx1 < MAX_POSSIBLE_MOVES_IN_POSITION; idx1 += 1) {
    cBoard->moves[idx1] = 0ULL;
  }
  cBoard->movesAvailable = 0;

  cBoard->positionKey = generateFullHash(cBoard);

  return 0;
}
