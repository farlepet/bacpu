#include <arithmetic.h>

// TODO: Find a better way to emulate ALU addition
uint32_t add32(uint32_t a, uint32_t b, int c)
{
    uint32_t result = 0;
    int carry = c & 1;
    int i = 0;

    for(; i < 32; i++)
    {
        result |= (((a ^ b) ^ carry) & 1) << i;
        carry  = (((a) & (b)) | ((a ^ b) & carry)) & 1;

        a >>= 1;
        b >>= 1;
    }

    return result;
}
