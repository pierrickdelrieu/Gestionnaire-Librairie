SOURCES=./sources/*.c
OUTPUT=./

main: clean
	gcc -o $(OUTPUT)/main $(SOURCES)

clean:
	rm -rf $(OUTPUT)/main

run:
	(cd $(OUTPUT) && ./main)

all: main run
