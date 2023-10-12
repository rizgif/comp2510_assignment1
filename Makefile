CC = gcc
CFLAGS = -Wall

# Executable name
EXECUTABLE = a1

LINE_LEN = 13
INPUT_FILE = input.txt
OUTPUT_FILE = output.txt
REFERENCE_OUTPUT_FILE = reference_output.txt

all: $(EXECUTABLE)

$(EXECUTABLE): a1.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) a1.c

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(LINE_LEN) $(INPUT_FILE) > $(OUTPUT_FILE)

test: run
	@echo "Comparing output with reference..."
	@diff $(OUTPUT_FILE) $(REFERENCE_OUTPUT_FILE) && echo "Test passed" || echo "Test failed"

clean:
	rm -f $(EXECUTABLE) $(OUTPUT_FILE)
