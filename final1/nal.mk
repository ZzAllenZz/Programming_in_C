# A single file (nal.c) is used to build the parser
# & interpreter & test_function & extent

CFLAGS = -Wall -Wextra -pedantic -ansi -O2 -lm
SFLAGS = -fsanitize=address -fsanitize=undefined -g3 -lm
DFLAGS = -Wall -Wextra -pedantic -ansi -g3 -lm
CC = clang
BASE = nal
BEXECS = parse interp test_function extent_parse extent_interp
SEXECS = parse_s interp_s test_function_s extent_parse extent_interp_d
DEXECS = parse_d interp_d test_function_d extent_parse extent_interp_d
EXECS = $(BEXECS) $(SEXECS) $(DEXECS)

all : $(BEXECS)


parse : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(CFLAGS) -o $@
parse_s : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(SFLAGS) -o $@
parse_d : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(DFLAGS) -o $@


interp : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(CFLAGS) -o $@ -DINTERP
interp_s : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(SFLAGS) -o $@ -DINTERP
interp_d : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(DFLAGS) -o $@ -DINTERP

#This is the third part to run my test function in test.c
#For all of parser, interpreter and extent
test_function : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c test.c $(CFLAGS) -o $@ -DTEST -DEXTENT
test_function_s : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c test.c $(SFLAGS) -o $@ -DTEST -DEXTENT
test_function_d : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c test.c $(DFLAGS) -o $@ -DTEST -DEXTENT

#This is parsing for the fourth part to run my extent code in extent.c
extent_parse : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c $(CFLAGS) -o $@ -DEXTENT
extent_parse_s : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c $(SFLAGS) -o $@ -DEXTENT
extent_parse_d : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c $(DFLAGS) -o $@ -DEXTENT

#This is interpreting for the fourth part to run my extent code in extent.c
extent_interp : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c $(CFLAGS) -o $@ -DEXTENT -DINTERP
extent_interp_s : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c $(SFLAGS) -o $@ -DEXTENT -DINTERP
extent_interp_d : $(BASE).c $(BASE).h mvm.c mvm.h extent.c extent.h
	$(CC) $(BASE).c mvm.c extent.c $(DFLAGS) -o $@ -DEXTENT -DINTERP



test_all : testparse testinterp

testparse : parse_s parse_d
	./parse_s test1.$(BASE)
	./parse_s test2.$(BASE)
	./parse_s test3.$(BASE)
	./parse_s test4.$(BASE)
	./parse_s test5.$(BASE)
	./parse_s test6.$(BASE)
	valgrind ./parse_d test1.$(BASE)
	valgrind ./parse_d test2.$(BASE)
	valgrind ./parse_d test3.$(BASE)
	valgrind ./parse_d test4.$(BASE)
	valgrind ./parse_d test5.$(BASE)
	valgrind ./parse_d test6.$(BASE)

testinterp : interp_s interp_d
	./interp_s test1.$(BASE)
	./interp_s test2.$(BASE)
	./interp_s test4.$(BASE)
	./interp_s test5.$(BASE)
	valgrind ./interp_d test1.$(BASE)
	valgrind ./interp_d test2.$(BASE)
	valgrind ./interp_d test4.$(BASE)
	valgrind ./interp_d test5.$(BASE)

#This is the third part to run my test function in test.c
#For all of parser, interpreter and extent
testfunction : test_function_s test_function_d
	./test_function_s test1.$(BASE)
	valgrind ./test_function_d test1.$(BASE)

#This is parsing for the fourth part to run my extent code in extent.c
testparse_extent : extent_parse_s extent_parse_d
	./extent_parse_s extent1.$(BASE)
	./extent_parse_s extent2.$(BASE)
	valgrind ./extent_parse_d extent1.$(BASE)
	valgrind ./extent_parse_d extent2.$(BASE)

#This is interpreting for the fourth part to run my extent code in extent.c
testinterp_extent : extent_interp_s extent_interp_d
	./extent_interp_s extent1.$(BASE)
	./extent_interp_s extent2.$(BASE)
	valgrind ./extent_interp_d extent1.$(BASE)
	valgrind ./extent_interp_d extent2.$(BASE)


clean :
	rm -fr $(EXECS)
