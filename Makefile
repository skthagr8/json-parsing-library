CC := g++
CFLAGS :=
OUT := 

ifeq ($(OS), Windows_NT)
	OUT := json.exe
else
	OUT := json.out
endif

.PHONY: clean

$(OUT): src/*.cpp
	$(CC) $(CFLAGS) $^ -o $@

run:
	./$(OUT)

clean:
	rm -f *.exe *.out