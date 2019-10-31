#include <stddef.h>

#include "move_gen_data_tests.h"

const char *fenPosToCheck[FEN_POS_TO_CHECK_LENGTH] = {
  // *******************************************
  // White king side castling. Various threats.
  // *******************************************

  // No threats - white king can castle king-side.
  "4k3/8/8/8/8/8/8/4K2R w K - 0 1",

  // Knight is only threatening the rook. White king can castle.
  "4k3/8/8/8/8/8/5n2/4K2R w K - 0 1",

  // In all below positions the white king can't king-side castle - since attacked by knight.
  "4k3/8/8/8/8/8/2n5/4K2R w K - 0 1",
  "4k3/8/8/8/8/3n4/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/5n2/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/8/6n1/4K2R w K - 0 1",

  // In all below positions the white king can't king-side castle - since passing square is attacked by knight.
  "4k3/8/8/8/8/8/3n4/4K2R w K - 0 1",
  "4k3/8/8/8/8/4n3/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/6n1/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/8/7n/4K2R w K - 0 1",

  // In all below positions the white king can't king-side castle - since finishing square is attacked by knight.
  "4k3/8/8/8/8/8/4n3/4K2R w K - 0 1",
  "4k3/8/8/8/8/5n2/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/7n/8/4K2R w K - 0 1",

  // *******************************************
  // White queen-side castling. Various threats.
  // *******************************************

  // No threats - white king can castle queen-side.
  "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1",

  // Knight is threatening both king and the rook. White king can't castle.
  "4k3/8/8/8/8/8/2n5/R3K3 w Q - 0 1",

  // Knight is threatening only the square the rook passes. White king can castle.
  "4k3/8/8/8/8/n7/8/R3K3 w Q - 0 1",

  // In all below positions the white king can't queen-side castle - since attacked by knight.
  "4k3/8/8/8/8/3n4/8/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/5n2/8/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/8/6n1/R3K3 w Q - 0 1",

  // In all below positions the white king can't queen-side castle - since passing square is attacked by knight.
  "4k3/8/8/8/8/8/1n6/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/2n5/8/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/4n3/8/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/8/5n2/R3K3 w Q - 0 1",

  // In all below positions the white king can't queen-side castle - since finishing square is attacked by knight.
  "4k3/8/8/8/8/8/n7/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/1n6/8/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/3n4/8/R3K3 w Q - 0 1",
  "4k3/8/8/8/8/8/4n3/R3K3 w Q - 0 1",

  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------

  // *******************************************
  // Black king side castling. Various threats.
  // *******************************************

  // No threats - black king can castle king-side.
  "4k2r/8/8/8/8/8/8/4K3 b k - 0 1",

  // Knight is only threatening the rook. Black king can castle.
  "4k2r/5N2/8/8/8/8/8/4K3 b k - 0 1",

  // In all below positions the black king can't king-side castle - since attacked by knight.
  "4k2r/2N5/8/8/8/8/8/4K3 b k - 0 1",
  "4k2r/8/3N4/8/8/8/8/4K3 b k - 0 1",
  "4k2r/8/5N2/8/8/8/8/4K3 b k - 0 1",
  "4k2r/6N1/8/8/8/8/8/4K3 b k - 0 1"

};
const char *movesToCheckForPos[FEN_POS_TO_CHECK_LENGTH][MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK] = {
  // *******************************************
  // White king side castling. Various threats.
  // *******************************************

  // No threats - white king can castle king-side.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "0-0", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // Knight is only threatening the rook. White king can castle.
  { "e1d1", "e1d2", "e1e2", "e1xf2", "e1f1", "0-0", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // In all below positions the white king can't king-side castle - since attacked by knight.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // In all below positions the white king can't king-side castle - since passing square is attacked by knight.
  { "e1d1", "e1xd2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1xh2", NULL },

  // In all below positions the white king can't king-side castle - since finishing square is attacked by knight.
  { "e1d1", "e1d2", "e1xe2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1xh3", NULL },

  // *******************************************
  // White queen-side castling. Various threats.
  // *******************************************

  // No threats - white king can castle queen-side.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "0-0-0", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },

  // Knight is threatening both king and the rook. White king can't castle.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },

  // Knight is threatening only the square the rook passes. White king can castle.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "0-0-0", "a1b1", "a1c1", "a1d1", "a1a2", "a1xa3", NULL },

  // In all below positions the white king can't queen-side castle - since attacked by knight.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },

  // In all below positions the white king can't queen-side castle - since passing square is attacked by knight.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1xf2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },

  // In all below positions the white king can't queen-side castle - since finishing square is attacked by knight.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1xa2", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },
  { "e1d1", "e1d2", "e1xe2", "e1f2", "e1f1", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL },

  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------

  // *******************************************
  // Black king side castling. Various threats.
  // *******************************************

  // No threats - black king can castle king-side.
  { "e8d8", "e8d7", "e8e7", "e8f7", "e8f8", "0-0", "h8g8", "h8f8", "h8h7", "h8h6", "h8h5", "h8h4", "h8h3", "h8h2", "h8h1", NULL },

  // Knight is only threatening the rook. Black king can castle.
  { "e8d8", "e8d7", "e8e7", "e8xf7", "e8f8", "0-0", "h8g8", "h8f8", "h8h7", "h8h6", "h8h5", "h8h4", "h8h3", "h8h2", "h8h1", NULL },

  // In all below positions the black king can't king-side castle - since attacked by knight.
  { "e8d8", "e8d7", "e8e7", "e8f7", "e8f8", "h8g8", "h8f8", "h8h7", "h8h6", "h8h5", "h8h4", "h8h3", "h8h2", "h8h1", NULL },
  { "e8d8", "e8d7", "e8e7", "e8f7", "e8f8", "h8g8", "h8f8", "h8h7", "h8h6", "h8h5", "h8h4", "h8h3", "h8h2", "h8h1", NULL },
  { "e8d8", "e8d7", "e8e7", "e8f7", "e8f8", "h8g8", "h8f8", "h8h7", "h8h6", "h8h5", "h8h4", "h8h3", "h8h2", "h8h1", NULL },
  { "e8d8", "e8d7", "e8e7", "e8f7", "e8f8", "h8g8", "h8f8", "h8h7", "h8h6", "h8h5", "h8h4", "h8h3", "h8h2", "h8h1", NULL }

};
