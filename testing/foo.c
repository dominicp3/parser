#include <stdint.h>
#include <stdio.h>

int64_t convert(const char *s)
{
        int64_t n = 0;
        do {
                n *= 10;
                n += *s - '0';
        } while (*++s);

        return n;
}

int main(void)
{
        printf("%lld\n", convert("3287645827635"));
        return 0;
}
