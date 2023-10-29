CC= clang
CFLAGS= -std=c99 -O3 -Wall -Wextra -pedantic -Werror -Werror=vla -fsanitize=address -g

.PHONY: clean

test: test.c obj/token.o obj/parse.o obj/lexer.o
	$(CC) $(CFLAGS) -o $@ $< $(filter obj/%.o, $^) -larray -lstack

obj/token.o: token.c token.h obj/
	$(CC) $(CFLAGS) -o $@ -c $<

obj/lexer.o: lexer.c lexer.h token.h obj/
	$(CC) $(CFLAGS) -o $@ -c $<

obj/parse.o: parse.c parse.h lexer.h token.h grammar.h obj/
	$(CC) $(CFLAGS) -o $@ -c $<

obj/grammar.o: grammar.c grammar.h token.h obj/
	$(CC) $(CFLAGS) -o $@ -c $<

obj/:
	mkdir $@

clean:
	rm -rf test obj *.dSYM
