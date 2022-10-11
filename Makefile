name := ProjetBTD
include_path := ./dep/include/
lib_path := ./dep/lib/

all: default

default:
	@g++ src/main.cpp -o ./${name}.exe -O2 -Wall -Wno-missing-braces -I ${include_path} -L ${lib_path} -lraylib -lopengl32 -lgdi32 -lwinmm
	@./${name}.exe
