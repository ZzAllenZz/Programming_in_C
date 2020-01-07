CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
DFLAGS = -g3 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
SFLAGS = -g3 -fsanitize=undefined -fsanitize=address
TESTBASE = nal
SOURCES =  $(TESTBASE).c
EXECS = $(TESTBASE) $(TESTBASE)_d $(TESTBASE)_s
CC = clang

run: $(TESTBASE)
	./$(TESTBASE) test1.nal

all: $(EXECS)

$(TESTBASE): $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(CFLAGS) -DINTERP

$(TESTBASE)_d: $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(DFLAGS) -DINTERP

$(TESTBASE)_s: $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(SFLAGS) -DINTERP

clean:
	rm -f $(EXECS)

memleaks: $(TESTBASE)_d $(TESTBASE)_s
	@echo "Sanitize :"
	@./$(TESTBASE)_s test1.nal
	@echo "Valgrind :"
	@valgrind --leak-check=full ./$(TESTBASE)_d test1.nal

