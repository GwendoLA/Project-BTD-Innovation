name := ProjetBTD
include_path := ./dep/include/
lib_path := ./dep/lib/

default:
	@g++ src/main.cpp -o ./build/${name}.exe -O2 -Wall -Wno-missing-braces -I ${include_path} -L ${lib_path} -lraylib -lopengl32 -lgdi32 -lwinmm
	@./build/${name}.exe