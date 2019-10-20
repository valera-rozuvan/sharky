#include "perft_tests.h"

/*
 *
 * Some known perft FEN strings. Taken from:
 *
 *   - https://www.chessprogramming.org/Perft_Results
 *
 *   - http://www.talkchess.com/forum3/viewtopic.php?t=60102
 *   - http://www.talkchess.com/forum3/viewtopic.php?t=60114
 *   - http://www.talkchess.com/forum3/viewtopic.php?t=59781
 *   - http://www.talkchess.com/forum3/viewtopic.php?t=59818
 *   - http://www.talkchess.com/forum3/viewtopic.php?t=59915
 *   - http://www.talkchess.com/forum3/viewtopic.php?t=59957
 *   - http://www.talkchess.com/forum3/viewtopic.php?t=59961
 *
 *   - http://www.rocechess.ch/perft.html
 *   - https://web.archive.org/web/20120722190602/http://www.albert.nu/programs/sharper/perft.asp
 *
 */

const char *PEFRT_FEN_STRINGS[PEFRT_FEN_STRINGS_LENGTH] = {
  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
  "rnb1kbnr/ppp1pppp/3p4/1q6/2BPP3/8/PPPQ1PPP/RNB1K1NR b KQkq - 2 4",
  "rnb1kbnr/ppp1pppp/3p4/5q2/6Q1/4PNP1/PPPP1P1P/RNB1KB1R b KQkq - 0 4",
  "rnQ1kbnr/p1p1pppp/3p4/5b2/8/4P3/PPPP1PPP/RNB1KBNR b KQkq - 0 4",
  "rnQ1kbnr/p1p1pppp/3p4/8/6b1/4P3/PPPP1PPP/RNB1KBNR b KQkq - 0 4",
  "rnQ1kbnr/p1p1pppp/3p4/8/8/4P2b/PPPP1PPP/RNB1KBNR b KQkq - 0 4",
  "rnQ1kbnr/p1p1pppp/3pb3/8/8/4P3/PPPP1PPP/RNB1KBNR b KQkq - 0 4",
  "rnQ1kbnr/p1pbpppp/3p4/8/8/4P3/PPPP1PPP/RNB1KBNR b KQkq - 0 4",
  "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",
  "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1",
  "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1",
  "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10",
  "rn1qkbnr/ppp2ppp/3pp3/8/3PP1b1/5Q2/PPP2PPP/RNB1KBNR b KQkq - 0 4",
  "rnb1kbnr/pp1pp1pp/1qp2p2/8/Q1P5/N7/PP1PPPPP/1RB1KBNR b Kkq - 2 4",
  "rnbq1b1r/ppppkppp/4pn2/8/1Q6/2PP4/PP2PPPP/RNB1KBNR b KQ - 2 4",
  "rnbq1bnr/ppppk1pp/5p2/4p3/1Q6/2PP4/PP2PPPP/RNB1KBNR b KQ - 2 4",
  "rnbqk1nr/p1pp1ppp/1p6/2b1p1B1/8/1QPP4/PP2PPPP/RN2KBNR b KQkq - 2 4",
  "rnb1kbnr/ppp1pppp/8/3p4/1P6/P2P3q/2P1PPP1/RNBQKBNR b KQkq - 0 4",
  "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1",
  "8/3K4/2p5/p2b2r1/5k2/8/8/1q6 b - - 1 67",
  "8/7p/p5pb/4k3/P1pPn3/8/P5PP/1rB2RK1 b - d3 0 28",
  "rnbqkb1r/ppppp1pp/7n/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3"
};
