CC= clang
CFLAGS= -std=c18 -Wall -Wextra -pedantic -Werror -Werror=vla
INCLUDE= -I./lexer -I./parser -I./token -I./evaluate
DEBUG= -fsanitize=address -g

COMPILE= $(CC) $(CFLAGS) $(INCLUDE)

.PHONY: clean

bin/test: testing/test.c obj/evaluate.o obj/ast.o obj/token.o obj/parser.o obj/lexer.o bin/
	$(COMPILE) $(DEBUG) -o $@ $< $(filter obj/%.o, $^) -larray -lstack -ltree

bin/foo: testing/foo.c bin/
	$(COMPILE) $(DEBUG) -o $@ $< -lstack

obj/token.o: token/token.c token/token.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/lexer.o: lexer/lexer.c lexer/lexer.h token/token.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/parser.o: parser/parser.c parser/parser.h lexer/lexer.h token/token.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/ast.o: parser/ast.c parser/ast.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/evaluate.o: evaluate/evaluate.c evaluate/evaluate.h obj/
	$(COMPILE) $(DEBUG) -o $@ -c $<

obj/:
	mkdir $@

bin/:
	mkdir $@

clean:
	rm -rf bin/ obj/ *.dSYM
