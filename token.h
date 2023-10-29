#ifndef _____TOKEN_H_____
#define _____TOKEN_H_____

#include <stdint.h>

enum TOKEN_TYPE {
/* 0 */ DEFAULT_TYPE,
/* 1 */	INT_TYPE, 
/* 2 */	OPERATION_TYPE,
/* 3 */	OPEN_BRACKET_TYPE,
/* 4 */	CLOSED_BRACKET_TYPE,
/* 5 */ SPECIAL_TYPE, /* eg $ */
/* 6 */	ERROR_TYPE
};

/*
typedef union {
	int64_t integer;
	char symbol;
} data;

typedef struct {
	data d;
	enum TOKEN_TYPE;
} token;
*/


typedef struct {
	char buff[100];
	enum TOKEN_TYPE type;
} token;


enum TOKEN_TYPE token_type_char(char c);
void token_clear(token *tkn);
void token_set(token *tkn, const char *s, enum TOKEN_TYPE t);
void token_append(token *tkn, char c);

#endif /* _____TOKEN_H_____ */
