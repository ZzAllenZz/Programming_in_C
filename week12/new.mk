CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
DFLAGS = -g3 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
SFLAGS = -g3 -fsanitize=undefined -fsanitize=address
TESTBASE = nal
SOURCES =  $(TESTBASE).c
EXECS = $(TESTBASE) $(TESTBASE)_d $(TESTBASE)_s
CC = clang

run: $(TESTBASE)
	./$(TESTBASE) escape211.nal

all: $(EXECS)

$(TESTBASE): $(SOURCES) mvm.c mvm.h
	$(CC) $(SOURCES) -o $@ $(CFLAGS) -DINTERP

$(TESTBASE)_d: $(SOURCES) mvm.c mvm.h
	$(CC) $(SOURCES) -o $@ $(DFLAGS) -DINTERP

$(TESTBASE)_s: $(SOURCES) mvm.c mvm.h
	$(CC) $(SOURCES) -o $@ $(SFLAGS) -DINTERP

clean:
	rm -f $(EXECS)

memleaks: $(TESTBASE)_d $(TESTBASE)_s
	@echo "Sanitize :"
	@./$(TESTBASE)_s escape211.nal
	@echo "Valgrind :"
	@valgrind --leak-check=full ./$(TESTBASE)_d escape211.nal

