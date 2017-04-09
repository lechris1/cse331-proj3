PROJECT=ProjectHashTable
# used as a backup
TESTING_FILE=/user/cse331/testing/run_tests

objs=main.o
files=main.cpp HashTable.h

CC=g++
CPPFLAGS := $(CPPFLAGS) -std=c++11 -Wall -g

output_file = $(PROJECT)

.PHONY: all
all: $(output_file)

$(output_file): $(files)
	sed -i "s/^#define UNIT_TEST/\/\/#define UNIT_TEST/g" ./HashTable.h 2>/dev/null | true;
	sed -i "" "s/^#define UNIT_TEST/\/\/#define UNIT_TEST/g" ./HashTable.h 2>/dev/null | true;

	$(CC) $(CPPFLAGS) main.cpp -o $(PROJECT)

.PHONY: test
test:
	$(TESTING_FILE) || ./run_tests;

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.gch
	rm -f $(PROJECT)

	cd ./tests; \
	./cmake_clean; \
	cd .. ; \
