#include <stddef.h>

#include "move_gen_tests_data.h"

const char *fenPosToCheck[FEN_POS_TO_CHECK_LENGTH] = {
  // *******************************************
  // White king side castling. Various threats.
  // *******************************************

  // No threats - king can castle.
  "4k3/8/8/8/8/8/8/4K2R w K - 0 1",

  // Knight is only threatening the rook. King can castle.
  "4k3/8/8/8/8/8/5n2/4K2R w K - 0 1",

  // In all below positions the king can't castle - since attacked by knight.
  "4k3/8/8/8/8/8/2n5/4K2R w K - 0 1",
  "4k3/8/8/8/8/3n4/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/5n2/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/8/6n1/4K2R w K - 0 1",

  // In all below positions the king can't castle - since passing square is attacked by knight.
  "4k3/8/8/8/8/8/3n4/4K2R w K - 0 1",
  "4k3/8/8/8/8/4n3/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/6n1/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/8/7n/4K2R w K - 0 1",

  // In all below positions the king can't castle - since finishing square is attacked by knight.
  "4k3/8/8/8/8/8/4n3/4K2R w K - 0 1",
  "4k3/8/8/8/8/5n2/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/7n/8/4K2R w K - 0 1",

  // *******************************************
  // White queen side castling.
  "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1"
};
const char *movesToCheckForPos[FEN_POS_TO_CHECK_LENGTH][MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK] = {
  // *******************************************
  // White king side castling. Various night threats.
  // *******************************************

  // No threats - king can castle.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "0-0", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // Knight is only threatening the rook. King can castle.
  { "e1d1", "e1d2", "e1e2", "e1xf2", "e1f1", "0-0", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // In all below positions the king can't castle - since attacked by knight.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // In all below positions the king can't castle - since passing square is attacked by knight.
  { "e1d1", "e1xd2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1xh2", NULL },

  // In all below positions the king can't castle - since finishing square is attacked by knight.
  { "e1d1", "e1d2", "e1xe2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1xh3", NULL },

  // *******************************************
  // White queen side castling.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "0-0-0", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL }
};
