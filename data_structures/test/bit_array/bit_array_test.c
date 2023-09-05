#include <stdio.h>  /* Printf, puts*/
#include <limits.h> /* ULONG_MAX*/
#include <stddef.h> /* size_t */

#include "bit_array.h"   /* Internal use */
/*****************************************************************************/

void FlipTest(void);

void SetBitTest(void);

void SetOnOffBitTest(void);

void GetBitTest(void);

void SetOnAllTest(void);

void RotateTest(void);

void ToStringTest(void);

void MirrorTest(void);

/*****************************************************************************/
int main(void)
{
    FlipTest();

    SetBitTest();

    SetOnOffBitTest();

    GetBitTest();

    SetOnAllTest();

    RotateTest();

    ToStringTest();

    MirrorTest();

    return 0;
}
/*****************************************************************************/
void FlipTest(void)
{
    puts("\n\n-------- Test 1 - Flip bit --------\n\n");

    if(2147506371 == BitArrFlipBit(2147506387, 4))
    {
        puts("BitArrFlipBit(2147506387, 4) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrFlipBit(2147506387, 4) - Fails.");
        puts("\n");
    }

    if(4096 == BitArrFlipBit(0, 12))
    {
        puts("BitArrFlipBit(0, 12) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrFlipBit(0, 12) - Fails.");
        puts("\n");
    }

    if(0X7FFFFFFFFFFFFFFF == BitArrFlipBit(ULONG_MAX, 63))
    {
        puts("BitArrFlipBit(ULONG_MAX, 63) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrFlipBit(ULONG_MAX, 63) - Fails.");
        puts("\n");
    }

    if(128 == BitArrFlipBit(0, 7))
    {
        puts("BitArrFlipBit(0, 7) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrFlipBit(0, 7) - Fails.");
    }
    puts("\n\n");

}
/*****************************************************************************/
void SetBitTest(void)
{
    puts("\n\n-------- Test 2 - Set bit --------\n\n");

    if(536877701 == BitArrSetBit(536877701 , 7, 1))
    {
        puts("BitArrSetBit(536877701 , 7, 1) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetBit(536877701 , 7, 1) - Fails.");
        puts("\n");
    }

    if(536877573 == BitArrSetBit(536877701 , 7, 0))
    {
        puts("BitArrSetBit(536877701 , 7, 0) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetBit(536877701 , 7, 0) - Fails.");
        puts("\n");
    }

    if(0x7FFFFFFFFFFFFFFF == BitArrSetBit(ULONG_MAX , 63, 0))
    {
        puts("BitArrSetBit(ULONG_MAX , 63, 0) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetBit(ULONG_MAX , 63, 0) - Fails.");
        puts("\n");
    }

    if(0xFFFFFFFFFFFFFFFF == BitArrSetBit(ULONG_MAX , 63, 1))
    {
        puts("BitArrSetBit(ULONG_MAX , 63, 1) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetBit(ULONG_MAX , 63, 1) - Fails.");
        puts("\n");
    }

    if(4096 == BitArrSetBit(0 , 12, 1))
    {
        puts("BitArrSetBit(0 , 63, 0) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetBit(0 , 63, 0) - Fails.");
        puts("\n");
    }
    puts("\n\n");

}
/*****************************************************************************/
void SetOnOffBitTest(void)
{
    puts("\n\n-------- Test 3 - Set all off/on bit --------\n\n");

    if(ULONG_MAX == BitArrSetOnAll(12))
    {
        puts("BitArrSetOnAll(12) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetOnAll(12) - Fails.");
        puts("\n");
    }

    if(ULONG_MAX == BitArrSetOnAll(ULONG_MAX))
    {
        puts("BitArrSetOnAll(ULONG_MAX) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetOnAll(ULONG_MAX) - Fails.");
        puts("\n");
    }

    if(ULONG_MAX == BitArrSetOnAll(0))
    {
        puts("BitArrSetOnAll(0) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetOnAll(0) - Fails.");
        puts("\n");
    }
    /*-----------------------------------------*/
    if(0 == BitArrSetOffAll(12))
    {
        puts("BitArrSetOffAll(12) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetOffAll(12) - Fails.");
        puts("\n");
    }

    if(0 == BitArrSetOffAll(ULONG_MAX))
    {
        puts("BitArrSetOffAll(ULONG_MAX) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetOffAll(ULONG_MAX) - Fails.");
        puts("\n");
    }

    if(0 == BitArrSetOffAll(0))
    {
        puts("BitArrSetOffAll(0) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrSetOffAll(0) - Fails.");
        puts("\n");
    }
    puts("\n\n");

}
/*****************************************************************************/
void GetBitTest(void)
{
    puts("\n\n-------- Test 4 - Getbit --------\n\n");

    if(0 == BitArrGetBit(134, 6))
    {
        puts("BitArrGetBit(134, 6) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrGetBit(134, 6) - Fails.");
        puts("\n");
    }

    if(1 == BitArrGetBit(134, 7))
    {
        puts("BitArrGetBit(134, 7) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrGetBit(134, 7) - Fails.");
        puts("\n");
    }

    if(0 == BitArrGetBit(0, 6))
    {
        puts("BitArrGetBit(0, 6) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrGetBit(0, 6) - Fails.");
        puts("\n");
    }

    puts("\n\n");

}
/*****************************************************************************/
void SetOnAllTest(void)
{
    puts("\n\n-------- Test 5 - CountOnBits/Off --------\n\n");

    MakeTable();

    if(2 == BitArrCountOnBits(6))
    {
        puts("BitArrCountOnBits(6) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOnBits(6) - Fails.");
        puts("\n");
    }

    if(40 == BitArrCountOnBits(0xFFFFFFFFFF))
    {
        puts("BitArrCountOnBits(0xFFFFFFFFFF) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOnBits(0xFFFFFFFFFF) - Fails.");
        puts("\n");
    }

    if(64 == BitArrCountOnBits(ULONG_MAX))
    {
        puts("BitArrCountOnBits(ULONG_MAX) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOnBits(ULONG_MAX) - Fails.");
        puts("\n");
    }

    if(9 == CountBitOnLUT(73532742))
    {
        puts("BitArrCountOnBits(73532742) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOnBits(73532742) - Fails.");
        puts("\n");
    }
    /*-----------------------------------------*/
    if(32 == BitArrCountOffBits(0xFFFFFFFF))
    {
        puts("BitArrCountOffBits(0xFFFFFFFF) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOffBits(0xFFFFFFFF) - Fails.");
        puts("\n");
    }

    if(64 == BitArrCountOffBits(0))
    {
        puts("BitArrCountOffBits(0) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOffBits(0) - Fails.");
        puts("\n");
    }

    if(0 == BitArrCountOffBits(ULONG_MAX))
    {
        puts("BitArrCountOffBits(ULONG_MAX) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOffBits(ULONG_MAX) - Fails.");
        puts("\n");
    }

    if(32 == BitArrCountOffBits(0xAAAAAAAAAAAAAAAA))
    {
        puts("BitArrCountOffBits(0xAAAAAAAAAAAAAAAA) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrCountOffBits(0xAAAAAAAAAAAAAAAA) - Fails.");
        puts("\n");
    }

    puts("\n\n");

}
/*****************************************************************************/
void RotateTest(void)
{
    puts("\n\n-------- Test 6 - Rotete Left/Right --------\n\n");

    if(0xAAAAAAAAAAAAAAAA == BitArrRotateLeft(0xAAAAAAAAAAAAAAAA, 234))
    {
        puts("BitArrRotateLeft(0xAAAAAAAAAAAAAAAA, 234) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrRotateLeft(0xAAAAAAAAAAAAAAAA, 234) - Fails.");
        puts("\n");
    }

    if(0 == BitArrRotateLeft(0, 54))
    {
        puts("BitArrRotateLeft(0, 54) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrRotateLeft(0, 54) - Fails.");
        puts("\n");
    }

    if(0xAFBAECCCCEAFBBC6 == BitArrRotateLeft(0x6AFBAECCCCEAFBBC, 4))
    {
        puts("BitArrRotateLeft(0x6AFBAECCCCEAFBBC, 4) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrRotateLeft(0x6AFBAECCCCEAFBBC, 4) - Fails.");
        puts("\n");
    }

    /*------------------------------------------------------*/

    if(0xAAAAAAAAAAAAAAAA == BitArrRotateRight(0xAAAAAAAAAAAAAAAA, 234))
    {
        puts("BitArrRotateRight(0xAAAAAAAAAAAAAAAA, 234) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrRotateRight(0xAAAAAAAAAAAAAAAA, 234) - Fails.");
        puts("\n");
    }

    if(0 == BitArrRotateRight(0, 54))
    {
        puts("BitArrRotateRight(0, 54) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrRotateRight(0, 54) - Fails.");
        puts("\n");
    }


    if(0xC6AFBAECCCCEAFBB == BitArrRotateRight(0x6AFBAECCCCEAFBBC, 4))
    {
        puts("BitArrRotateRight(0x6AFBAECCCCEAFBBC, 4) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrRotateRight(0x6AFBAECCCCEAFBBC, 4) - Fails.");
        puts("\n");
    }

    puts("\n\n");

}
/*****************************************************************************/
void ToStringTest(void)
{
    char str[70] = "0";
    char str1[70] = "0";
    char str2[70] = "0";
    char str3[70] = "0";
    BitArrToString(0xFFFFFFFFFFFFFFFF, str);
    BitArrToString(0, str1);
    BitArrToString(0xCCCCCCCCCCCCCCCC, str2);
    BitArrToString(1234567890, str3);

    puts("\n\n-------- Test 7 - To String --------\n\n");

    printf("0xFFFFFFFFFFFFFFFF = %s\n", str);
    printf("\n0 = %s\n", str1);
    printf("\n0xCCCCCCCCCCCCCCCC = %s\n", str2);
    printf("\n1234567890 = %s\n", str3);

    puts("\n\n");
}
/*****************************************************************************/
void MirrorTest(void)
{
    puts("\n\n-------- Test 8 - Mirror bit --------\n\n");

    if(0xF == BitArrMirror(0xF000000000000000))
    {
        puts("BitArrMirror(0xF000000000000000) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrMirror(0xF000000000000000) - Fails.");
        puts("\n");
    }

    if(0x98640F0800000000 == BitArrMirror(0x10F02619))
    {
        puts("BitArrMirror(0x10F02619) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrMirror(0x10F02619) - Fails.");
        puts("\n");
    }

    if(0x0 == BitArrMirror(0x0))
    {
        puts("BitArrMirror(0x0) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrMirror(0x0) - Fails.");
        puts("\n");
    }

    if(0x21004C0010F02619 == BitArrMirror(0x98640F0800320084))
    {
        puts("BitArrMirror(0x98640F0800320084) - Passed.");
        puts("\n");
    }
    else
    {
        puts("BitArrMirror(0x98640F0800320084) - Fails.");
        puts("\n");
    }

    puts("\n\n");
}
/*****************************************************************************/
