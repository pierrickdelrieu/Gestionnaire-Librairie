SOURCES=./sources/*.c
HEADERS=./headers
OUTPUT=./

main: clean
	gcc -o $(OUTPUT)/main $(SOURCES) -I $(HEADERS)

clean:
	rm -rf $(OUTPUT)/main

run:
	(cd $(OUTPUT) && ./main)

all: main run
