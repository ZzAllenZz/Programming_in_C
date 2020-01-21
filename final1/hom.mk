CFLAGS = -O2 -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi -lm
DFLAGS = -g3 -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi -lm
SFLAGS = -g3 -fsanitize=undefined -fsanitize=address -lm
TESTBASE = nal
INCS = mvm.h
SOURCES =  $(TESTBASE).c mvm.c
EXECS = $(TESTBASE) $(TESTBASE)_d $(TESTBASE)_s nal
CC = clang

run: $(TESTBASE)
	./$(TESTBASE) test1.nal

all: $(EXECS)

$(TESTBASE): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

$(TESTBASE)_d: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(DFLAGS) 

$(TESTBASE)_s: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(SFLAGS) 

clean:
	rm -f $(EXECS)

memleaks: $(TESTBASE)_d $(TESTBASE)_s
	@echo "Sanitize :"
	@./$(TESTBASE)_s  test1.nal
	@echo "Valgrind :"
	@valgrind --leak-check=full ./$(TESTBASE)_d test1.nal

