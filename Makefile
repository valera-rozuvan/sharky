# TODO: Try to simplify. For example, see:
# https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory

all: obj/sharky.o obj/board_routines.o
	gcc -o build/sharky obj/sharky.o obj/board_routines.o

obj/sharky.o:
	gcc -c src/sharky.c -o obj/sharky.o

obj/board_routines.o:
	gcc -c src/board_routines.c -o obj/board_routines.o

clean:
	rm build/sharky obj/*.o

