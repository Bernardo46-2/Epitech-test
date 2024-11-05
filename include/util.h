#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_SIZE 0xffffffffffffffff

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

// typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;

typedef float float32_t;
typedef double float64_t;

/**
 * @brief Calculates the absolute value of an integer
 *
 * @param x Integer to get abs value from
 * @return Abs value of number
 */
int abs(int x);

#endif
