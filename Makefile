SOURCES=./sources/*.c
HEADERS=./headers
OUTPUT=./
COMPILER=clang
STD=c11

main: clean
	$(COMPILER) -std=$(STD) -o $(OUTPUT)/main $(SOURCES) -I $(HEADERS)

clean:
	rm -rf $(OUTPUT)/main

run:
	(cd $(OUTPUT) && ./main)

all: main run
