/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Yonatan longini           ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date: 28.02.2023                    ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h> /* size_t */

typedef size_t bitarr_t;

/* 
	index should be between 0 and 63 
	value should be 0 or 1
*/

/* Flip the value of an indexed bit */
bitarr_t BitArrFlipBit(bitarr_t, size_t);

/* Set the bit at index location to value*/
bitarr_t BitArrSetBit(bitarr_t, size_t, int);

/* Set the bit on at index location*/
bitarr_t BitArrSetOnBit(bitarr_t, size_t);

/* Set off the bit at index location*/
bitarr_t BitArrSetOffBit(bitarr_t, size_t);

/* Set all bits on */
bitarr_t BitArrSetOnAll (bitarr_t);

/* Set off all bits */
bitarr_t BitArrSetOffAll(bitarr_t);

/* Gets the bit at index location */
int BitArrGetBit(bitarr_t, size_t);

/* Count all the bits that are on */
size_t BitArrCountOnBits(bitarr_t);

/* Count all the bits that are Off */
size_t BitArrCountOffBits(bitarr_t);

/* Rotate the bits Left num times */
bitarr_t BitArrRotateLeft(bitarr_t, size_t);

/* Rotate the bits Right num times */
bitarr_t BitArrRotateRight(bitarr_t, size_t);

/* Return a string of the bits */
char *BitArrToString(bitarr_t, char *);

/* Mirror the bit array */
bitarr_t BitArrMirror(bitarr_t);

/* LUT implementation */
bitarr_t CountBitOnLUT(bitarr_t bitarr);

/*Making the LUT table */
void MakeTable(void);

#endif /* __BIT_ARRAY_H__ */
