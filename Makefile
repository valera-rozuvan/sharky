# TODO: Try to simplify. For example, see:
# https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory

# CFLAGS =
#   -pedantic
CFLAGS = -DVASSERT_ENABLE -Wall -Wextra -Werror -std=c99 -pedantic

MAIN_OBJECTS = \
	obj/board_routines.o \
	obj/vassert.o \
	obj/bitboard.o \
	obj/random_const.o \
	obj/zobrist_hashing.o

all: obj/sharky.o $(MAIN_OBJECTS)
	gcc -o build/sharky obj/sharky.o $(MAIN_OBJECTS)

obj/sharky.o: src/sharky.c
	gcc -c $(CFLAGS) src/sharky.c -o obj/sharky.o

obj/board_routines.o: src/board_routines.c src/board_routines.h
	gcc -c $(CFLAGS) src/board_routines.c -o obj/board_routines.o

obj/vassert.o: src/vassert.c src/vassert.h
	gcc -c $(CFLAGS) src/vassert.c -o obj/vassert.o

obj/bitboard.o: src/bitboard.c src/bitboard.h
	gcc -c $(CFLAGS) src/bitboard.c -o obj/bitboard.o

obj/random_const.o: src/random_const.c src/random_const.h
	gcc -c $(CFLAGS) src/random_const.c -o obj/random_const.o

obj/zobrist_hashing.o: src/zobrist_hashing.c src/zobrist_hashing.h
	gcc -c $(CFLAGS) src/zobrist_hashing.c -o obj/zobrist_hashing.o

clean:
	rm -rf build/sharky build/tests obj/*.o

TESTS_OBJECTS = \
        obj/random_const_tests.o \
        obj/board_routines_tests.o \
        obj/bitboard_tests.o \
        obj/zobrist_hashing_tests.o

test: obj/tests.o $(TESTS_OBJECTS) $(MAIN_OBJECTS)
	gcc -o build/tests obj/tests.o $(TESTS_OBJECTS) $(MAIN_OBJECTS)

obj/tests.o: tests/tests.c
	gcc -c $(CFLAGS) tests/tests.c -o obj/tests.o

obj/random_const_tests.o: tests/random_const_tests.c tests/random_const_tests.h
	gcc -c $(CFLAGS) tests/random_const_tests.c -o obj/random_const_tests.o

obj/board_routines_tests.o: tests/board_routines_tests.c tests/board_routines_tests.h
	gcc -c $(CFLAGS) tests/board_routines_tests.c -o obj/board_routines_tests.o

obj/bitboard_tests.o: tests/bitboard_tests.c tests/bitboard_tests.h
	gcc -c $(CFLAGS) tests/bitboard_tests.c -o obj/bitboard_tests.o

obj/zobrist_hashing_tests.o: tests/zobrist_hashing_tests.c tests/zobrist_hashing_tests.h
	gcc -c $(CFLAGS) tests/zobrist_hashing_tests.c -o obj/zobrist_hashing_tests.o
