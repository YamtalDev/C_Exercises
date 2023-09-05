/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Yonatan Longini           ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date: 28.02.2023                    ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <stddef.h> /* size_t, NULL*/
#include <limits.h> /* CHAR_BIT , ULONG_MAX*/
#include <assert.h> /* assert */

#include "bit_array.h"   /* Internal use */
#define MAX_INDEXS (sizeof(bitarr_t) * CHAR_BIT)
#define WORD_BIT (sizeof(size_t) * CHAR_BIT)

char Table[256] = {0};
/*****************************************************************************/
void MakeTable(void)
{
    int i = 0;
    for(; i < 256; ++i)
    {
        *(Table + i) = (i & 1) + *(Table + i / 2);
    }
}
/*****************************************************************************/
bitarr_t BitArrFlipBit(bitarr_t bitarr, size_t index)
{
    assert(index < MAX_INDEXS && "Index out of bound");

    return bitarr ^ (bitarr_t)((size_t)1 << index);
}
/*****************************************************************************/
bitarr_t BitArrSetBit(bitarr_t bitarr, size_t index, int value)
{
    assert(index < MAX_INDEXS && "Index out of bound");

    return (bitarr & ~(bitarr_t)((size_t)1 << index)) | (bitarr_t)(value << index);
}
/*****************************************************************************/
bitarr_t BitArrSetOnBit(bitarr_t bitarr,size_t index)
{
    assert(index < MAX_INDEXS && "Index out of bound");

    return bitarr | (bitarr_t)((size_t)1 << index);
}
/*****************************************************************************/
bitarr_t BitArrSetOffBit(bitarr_t bitarr,size_t index)
{
    assert(index < MAX_INDEXS && "Index out of bound");

    return bitarr & (~(bitarr_t)((size_t)1 << index));
}
/*****************************************************************************/
bitarr_t BitArrSetOnAll(bitarr_t bitarr)
{
    (void)bitarr;
    return (bitarr & (bitarr_t)0);
}
/*****************************************************************************/
bitarr_t BitArrSetOffAll(bitarr_t bitarr)
{
    (void)bitarr;
    return (bitarr_t)0;
}
/*****************************************************************************/
int BitArrGetBit(bitarr_t bitarr, size_t index)
{
    assert(index < MAX_INDEXS && "Index out of bound");

    return !(bitarr & (bitarr_t)((size_t)1 << index)) == 0;
}
/*****************************************************************************/
size_t BitArrCountOnBits(bitarr_t bitarr)
{
    bitarr_t tmp = bitarr;

    bitarr_t mask1 = 0x5555555555555555;
    bitarr_t mask2 = 0x3333333333333333;
    bitarr_t mask3 = 0xF0F0F0F0F0F0F0F;
    bitarr_t mask4 = 0xFF00FF00FF00FF;
    bitarr_t mask5 = 0xFFFF0000FFFF;
    bitarr_t mask6 = 0xFFFFFFFF;

    /* Implementing mask AND, shifting bits to count the weight of tmp */
    tmp = (tmp & mask1) + ((tmp >> 1) & mask1);
    tmp = (tmp & mask2) + ((tmp >> 2) & mask2);
    tmp = (tmp & mask3) + ((tmp >> 4) & mask3);
    tmp = (tmp & mask4) + ((tmp >> 8) & mask4);
    tmp = (tmp & mask5) + ((tmp >> 16) & mask5);
    tmp = (tmp & mask6) + ((tmp >> 32) & mask6);

    /* The value of tmp is know the number of set bits */

    return tmp;
}
/*****************************************************************************/
bitarr_t CountBitOnLUT(bitarr_t bitarr)
{
    return Table[bitarr & 0xFF] + Table[(bitarr >> 8) & 0xFF] +
           Table[(bitarr >> 16) & 0xFF] + Table[(bitarr >> 24) & 0xFF] +
           Table[(bitarr >> 32) & 0xFF] + Table[(bitarr >> 40) & 0xFF] +
           Table[(bitarr >> 48) & 0xFF] + Table[(bitarr >> 56) & 0xFF];
}
/*****************************************************************************/
size_t BitArrCountOffBits(bitarr_t bitarr)
{
    return WORD_BIT - BitArrCountOnBits(bitarr);
}
/*****************************************************************************/
bitarr_t BitArrRotateLeft(bitarr_t bitarr, size_t num)
{
    return (bitarr << (bitarr_t)(num % 64)) | (bitarr >> (bitarr_t)(WORD_BIT - num % 64));
}
/*****************************************************************************/
bitarr_t BitArrRotateRight(bitarr_t bitarr, size_t num)
{
    return  (bitarr >> (bitarr_t)(num % 64)) | (bitarr << (bitarr_t)(WORD_BIT - num % 64));
}
/*****************************************************************************/
char *BitArrToString(bitarr_t bitarr, char *str)
{
    bitarr_t bits = WORD_BIT;

    if(NULL == str){ return str;}

    while(bits--)
    {
        *str = ((bitarr & (bitarr_t)((size_t)1 << bits)) > 0) + '0';
        str++;
    }

    *str = '\0';

    return str;
}
/*****************************************************************************/
bitarr_t BitArrMirror(bitarr_t bitarr)
{
    bitarr = bitarr << 32 | bitarr >> 32;
    bitarr = (bitarr & 0xFFFF0000FFFF) << 16 | (bitarr & 0xFFFF0000FFFF0000) >> 16;
    bitarr = (bitarr & 0xFF00FF00FF00FF) << 8 | (bitarr & 0xFF00FF00FF00FF00) >> 8;
    bitarr = (bitarr & 0xF0F0F0F0F0F0F0F) << 4 | (bitarr & 0xF0F0F0F0F0F0F0F0) >> 4;
    bitarr = (bitarr & 0x3333333333333333) << 2 | (bitarr & 0xCCCCCCCCCCCCCCCC) >> 2;
    bitarr = (bitarr & 0x5555555555555555) << 1 | (bitarr & 0XAAAAAAAAAAAAAAAA) >> 1;

    return bitarr;
}
/*****************************************************************************/
