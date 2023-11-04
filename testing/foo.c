#include <stdint.h>
#include <stdio.h>
#include <stack.h>
#include <string.h>

int64_t convert(const char *s)
{
        int64_t n = 0;
        do {
                n *= 10;
                n += *s - '0';
        } while (*++s);

        return n;
}

void switch_test(void)
{
        switch (5) {
        case 10: return;
        case 11: return;
        default:;
        }

        puts("end of switch statement");
}

void const_char(void)
{
        const char *c = "";

        c = "dominic";

        // c[0] = 'e';

        (void) c;

        printf("%s\n", c);
}

void push_chars_stack(stack__t *stk, char *str)
{
        if (!stk || !str)
                return;

        printf("%s\n", str);        
        // char c = 'X';
        // stack__t_push(stk, &c);

        printf("%lu\n", strlen(str));

        // size_t i;
        // for (i = strlen(str) - 1; i >= 0; i--) {
        //         printf("here: %c\n", *((char *) str + i));
        //         stack__t_push(stk, (char *) str + i);
        // }
}

void test_char_stack(void)
{
        stack__t *s = stack_init(sizeof(char));
        // push_chars_stack__t(s, "S$");
        char *str = "S$";
        for (size_t i = 0; i < 2; i++) {
                printf("HERE: %lu\n", i);
                stack_push(s, str + i);
        }
        stack_destroy(s);
}

int main(void)
{
        test_char_stack();
        return 0;
}
