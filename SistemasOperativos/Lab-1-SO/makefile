CC := gcc
CFLAGS := -Wall
EXECUTABLE := main
SOURCE := main.c
EXECUTABLE2 := mainOpti
SOURCE2 := mainOpti.c
CWD := CWD
H := horizontal
V := vertical
SIZE1 := 200x200
SIZE2 := 100x100
SIZE3 := 50x50

all: $(EXECUTABLE) $(EXECUTABLE2) crearCarpetas

crearCarpetas:
	mkdir -p $(CWD)/$(H)/$(SIZE1)
	mkdir -p $(CWD)/$(H)/$(SIZE2)
	mkdir -p $(CWD)/$(H)/$(SIZE3)
	mkdir -p $(CWD)/$(V)/$(SIZE1)
	mkdir -p $(CWD)/$(V)/$(SIZE2)
	mkdir -p $(CWD)/$(V)/$(SIZE3)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

$(EXECUTABLE2): $(SOURCE2)
	$(CC) $(CFLAGS) $(SOURCE2) -o $(EXECUTABLE2)

.PHONY: all crearCarpetas

run: $(EXECUTABLE)
	./$(EXECUTABLE)

runOpti: $(EXECUTABLE2)
	./$(EXECUTABLE2)
clean:
	rm -f $(EXECUTABLE)
	rm -f $(EXECUTABLE2)
