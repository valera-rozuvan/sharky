#ifndef __RANDOM_CONST_H__
#define __RANDOM_CONST_H__

/*
 * We have an array of random numbers to help us generate a hash for a game position.
 *
 *   - One number for each piece at each square (excluding squares where pawns can't be situated)
 *   - One number to indicate the side to move is black
 *   - Four numbers to indicate the castling rights
 *   - Eight numbers to indicate the file of a valid En passant square, if any
 *
 * So, in total, we have (12 * 64 - 2 * 16) + 1 + 4 + 8 = 749 random numbers.
 * We pre-compute them on special hardware and hard code them at compile time.
 */

#define RANDOM_CONST_LENGTH 749
extern unsigned long long RANDOM_CONST[RANDOM_CONST_LENGTH];

#endif // __RANDOM_CONST_H__
