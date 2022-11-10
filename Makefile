name := ProjetBTD
include_path := ./dep/include/
lib_path := ./dep/lib/

all: default

default:
	@g++ src/main.cpp -o ./${name}.exe -O2 -Wall -Wno-missing-braces -I ${include_path} -L ${lib_path} -lraylib -lopengl32 -lgdi32 -lwinmm
	@./${name}.exe
menu:
	echo starting
	@g++ src/menu.cpp -o ./${name}.exe -O2 -Wall -Wno-missing-braces -I ${include_path} -L ${lib_path} -lraylib -lopengl32 -lgdi32 -lwinmm
	@./${name}.exe
test:
	echo starting
	@g++ src/test.cpp -o ./${name}.exe -O2 -Wall -Wno-missing-braces -I ${include_path} -L ${lib_path} -lraylib -lopengl32 -lgdi32 -lwinmm
	@./${name}.exe

%.cpp: $(wildcard src/*.c)
	@echo $@
	@g++ src/$@ -o ./${name}.exe -O2 -Wall -Wno-missing-braces -I ${include_path} -L ${lib_path} -lraylib -lopengl32 -lgdi32 -lwinmm
	@./${name}.exe

%: $(wildcard *.cpp)
	@echo $@.cpp
	@g++ $@.cpp -o ./${name}.exe -O2 -Wall -Wno-missing-braces -I ${include_path} -L ${lib_path} -lraylib -lopengl32 -lgdi32 -lwinmm
	@./${name}.exe