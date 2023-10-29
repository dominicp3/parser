CC= clang
CFLAGS= -std=c99 -O3 -Wall -Wextra -pedantic -Werror -Werror=vla

INCLUDE= -I./include
DEBUG= -fsanitize=address -g

COMPILE= $(CC) $(CFLAGS) $(INCLUDE)

# INCLUDE= -I./grammar -I./lexer -I./parser -I./token

.PHONY: clean

bin/test: testing/test.c obj/token.o obj/parser.o obj/lexer.o bin/
	$(COMPILE) $(DEBUG) -o $@ $< $(filter obj/%.o, $^) -larray -lstack

bin/foo: testing/foo.c bin/
	$(COMPILE) $(DEBUG) -o $@ $<

obj/token.o: token/token.c token/token.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/lexer.o: lexer/lexer.c lexer/lexer.h token/token.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

#obj/grammar.o: grammar/grammar.c grammar/grammar.h token/token.h obj/
#	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/parser.o: parser/parser.c parser/parser.h lexer/lexer.h token/token.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/:
	mkdir $@

bin/:
	mkdir $@

clean:
	rm -rf bin/ obj/ *.dSYM

