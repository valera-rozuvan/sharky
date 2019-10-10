unsigned long long setBitMask[64];
unsigned long long clrBitMask[64];

void initBitMasks() {
  unsigned char idx = 0;

  for (idx = 0; idx < 64; idx += 1) {
    setBitMask[idx] = 0ULL | (1ULL << idx);
    clrBitMask[idx] = ~setBitMask[idx];
  }
}

/*
 * Below 2 functions, and the constant array, are taken from:
 *   https://www.chessprogramming.org/Looking_for_Magics
 */
unsigned char count_1s(unsigned long long b) {
  unsigned char r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
}

const unsigned char BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

unsigned char pop_1st_bit(unsigned long long *bb) {
  unsigned long long b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));

  *bb &= (*bb - 1);

  return BitTable[(fold * 0x783a9b23) >> 26];
}

