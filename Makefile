SOURCES=./sources/*.c
HEADERS=./headers
OUTPUT=./
COMPILER=clang
STD=c11

main: clean
	$(COMPILER) -ggdb3 -std=$(STD) -o $(OUTPUT)/main $(SOURCES) -I $(HEADERS)

clean:
	rm -rf $(OUTPUT)/main

run:
	(cd $(OUTPUT) && ./main)

debug: main
	gdb $(OUTPUT)/main

all: main run
