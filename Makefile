# TODO: Try to simplify. For example, see:
# https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory

# CFLAGS =
CFLAGS = -DVASSERT_ENABLE -O3 -Wall -Wextra -Werror -std=gnu99 -pedantic
# CFLAGS = -DVASSERT_ENABLE -g -Wall -Wextra -Werror -std=gnu99 -pedantic

GPROF =
#GPROF = -pg

MAIN_OBJECTS = \
	obj/board_routines.o \
	obj/vassert.o \
	obj/bitboard.o \
	obj/random_const.o \
	obj/zobrist_hashing.o \
	obj/fen.o \
	obj/get_real_time.o \
	obj/move_gen.o \
	obj/move_gen_white.o \
	obj/move_gen_black.o \
	obj/do_move.o

all: obj/sharky.o $(MAIN_OBJECTS)
	gcc -o build/sharky obj/sharky.o $(MAIN_OBJECTS) ${GPROF}

obj/sharky.o: src/sharky.c
	gcc -c $(CFLAGS) src/sharky.c -o obj/sharky.o ${GPROF}

obj/board_routines.o: src/board_routines.c src/board_routines.h
	gcc -c $(CFLAGS) src/board_routines.c -o obj/board_routines.o ${GPROF}

obj/vassert.o: src/vassert.c src/vassert.h
	gcc -c $(CFLAGS) src/vassert.c -o obj/vassert.o ${GPROF}

obj/bitboard.o: src/bitboard.c src/bitboard.h
	gcc -c $(CFLAGS) src/bitboard.c -o obj/bitboard.o ${GPROF}

obj/random_const.o: src/random_const.c src/random_const.h
	gcc -c $(CFLAGS) src/random_const.c -o obj/random_const.o ${GPROF}

obj/zobrist_hashing.o: src/zobrist_hashing.c src/zobrist_hashing.h
	gcc -c $(CFLAGS) src/zobrist_hashing.c -o obj/zobrist_hashing.o ${GPROF}

obj/fen.o: src/fen.c src/fen.h
	gcc -c $(CFLAGS) src/fen.c -o obj/fen.o ${GPROF}

obj/get_real_time.o: src/get_real_time.c src/get_real_time.h
	gcc -c $(CFLAGS) src/get_real_time.c -o obj/get_real_time.o ${GPROF}

obj/move_gen.o: src/move_gen.c src/move_gen.h
	gcc -c $(CFLAGS) src/move_gen.c -o obj/move_gen.o ${GPROF}

obj/move_gen_white.o: src/move_gen_white.c src/move_gen_white.h
	gcc -c $(CFLAGS) src/move_gen_white.c -o obj/move_gen_white.o ${GPROF}

obj/move_gen_black.o: src/move_gen_black.c src/move_gen_black.h
	gcc -c $(CFLAGS) src/move_gen_black.c -o obj/move_gen_black.o ${GPROF}

obj/do_move.o: src/do_move.c src/do_move.h
	gcc -c $(CFLAGS) src/do_move.c -o obj/do_move.o ${GPROF}

clean:
	rm -rf build/sharky build/tests build/perft obj/*.o

TESTS_OBJECTS = \
	obj/random_const_tests.o \
	obj/board_routines_tests.o \
	obj/bitboard_tests.o \
	obj/zobrist_hashing_tests.o \
	obj/fen_tests.o \
	obj/perft_tests.o \
	obj/move_gen_tests.o \
	obj/move_gen_data_tests.o \
	obj/do_move_tests.o

test: obj/tests.o $(TESTS_OBJECTS) $(MAIN_OBJECTS)
	gcc -o build/tests obj/tests.o $(TESTS_OBJECTS) $(MAIN_OBJECTS) ${GPROF}

obj/tests.o: tests/tests.c tests/tests.h
	gcc -c $(CFLAGS) tests/tests.c -o obj/tests.o ${GPROF}

obj/random_const_tests.o: tests/random_const_tests.c tests/random_const_tests.h
	gcc -c $(CFLAGS) tests/random_const_tests.c -o obj/random_const_tests.o ${GPROF}

obj/board_routines_tests.o: tests/board_routines_tests.c tests/board_routines_tests.h
	gcc -c $(CFLAGS) tests/board_routines_tests.c -o obj/board_routines_tests.o ${GPROF}

obj/bitboard_tests.o: tests/bitboard_tests.c tests/bitboard_tests.h
	gcc -c $(CFLAGS) tests/bitboard_tests.c -o obj/bitboard_tests.o ${GPROF}

obj/zobrist_hashing_tests.o: tests/zobrist_hashing_tests.c tests/zobrist_hashing_tests.h
	gcc -c $(CFLAGS) tests/zobrist_hashing_tests.c -o obj/zobrist_hashing_tests.o ${GPROF}

obj/fen_tests.o: tests/fen_tests.c tests/fen_tests.h
	gcc -c $(CFLAGS) tests/fen_tests.c -o obj/fen_tests.o ${GPROF}

obj/perft_tests.o: tests/perft_tests.c tests/perft_tests.h
	gcc -c $(CFLAGS) tests/perft_tests.c -o obj/perft_tests.o ${GPROF}

obj/move_gen_tests.o: tests/move_gen_tests.c tests/move_gen_tests.h
	gcc -c $(CFLAGS) tests/move_gen_tests.c -o obj/move_gen_tests.o ${GPROF}

obj/move_gen_data_tests.o: tests/move_gen_data_tests.c tests/move_gen_data_tests.h
	gcc -c $(CFLAGS) tests/move_gen_data_tests.c -o obj/move_gen_data_tests.o ${GPROF}

obj/do_move_tests.o: tests/do_move_tests.c tests/do_move_tests.h
	gcc -c $(CFLAGS) tests/do_move_tests.c -o obj/do_move_tests.o ${GPROF}

PERFT_OBJECTS =

perft: obj/perft.o $(PERFT_OBJECTS) $(MAIN_OBJECTS)
	gcc -o build/perft obj/perft.o $(PERFT_OBJECTS) $(MAIN_OBJECTS) ${GPROF}

obj/perft.o: perft/perft.c perft/perft.h
	gcc -c $(CFLAGS) perft/perft.c -o obj/perft.o ${GPROF}
