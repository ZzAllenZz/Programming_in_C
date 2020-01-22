CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
DFLAGS = -g3 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
SFLAGS = -g3 -fsanitize=undefined -fsanitize=address
TESTBASE = nal
INCS = mvm.h nal.h
SOURCES =  $(TESTBASE).c mvm.c test.c
EXECS = $(TESTBASE) $(TESTBASE)_d $(TESTBASE)_s
CC = clang

run: $(TESTBASE)
	./$(TESTBASE) test2.nal

all: $(EXECS)

$(TESTBASE): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

$(TESTBASE)_d: $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(DFLAGS)

$(TESTBASE)_s: $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(SFLAGS)

clean:
	rm -f $(EXECS)

memleaks: $(TESTBASE)_d $(TESTBASE)_s
	@echo "Sanitize :"
	@./$(TESTBASE)_s test2.nal
	@echo "Valgrind :"
	@valgrind --leak-check=full ./$(TESTBASE)_d test2.nal

