# TODO: Try to simplify. For example, see:
# https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory

# CFLAGS =
CFLAGS = -DVASSERT_ENABLE

all: obj/sharky.o obj/board_routines.o obj/vassert.o obj/bitboard.o obj/random_const.o
	gcc -o build/sharky obj/sharky.o obj/board_routines.o obj/vassert.o obj/bitboard.o obj/random_const.o

obj/sharky.o: src/sharky.c Makefile
	gcc -c $(CFLAGS) src/sharky.c -o obj/sharky.o

obj/board_routines.o: src/board_routines.c src/board_routines.h Makefile
	gcc -c $(CFLAGS) src/board_routines.c -o obj/board_routines.o

obj/vassert.o: src/vassert.c src/vassert.h Makefile
	gcc -c $(CFLAGS) src/vassert.c -o obj/vassert.o

obj/bitboard.o: src/bitboard.c src/bitboard.h Makefile
	gcc -c $(CFLAGS) src/bitboard.c -o obj/bitboard.o

obj/random_const.o: src/random_const.c src/random_const.h Makefile
	gcc -c $(CFLAGS) src/random_const.c -o obj/random_const.o

clean:
	rm -rf build/sharky obj/*.o

