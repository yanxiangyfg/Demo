#ifndef __FIFO_COMMON_H
#define __FIFO_COMMON_H


#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef __SIZE_TYPE__		size_t;
typedef signed long		ssize_t;
typedef signed long		off_t;

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long	uint64_t;

typedef signed char		int8_t;
typedef signed short		int16_t;
typedef signed int		int32_t;

typedef unsigned long		physaddr_t;

typedef unsigned long long u64;
typedef int64_t s64;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint8_t u8;
typedef int8_t s8;

typedef unsigned long long __u64;
typedef int64_t __s64;
typedef uint32_t __u32;
typedef int32_t __s32;
typedef uint16_t __u16;
typedef int16_t __s16;
typedef uint8_t __u8;
typedef int8_t __s8;



#define BITS_PER_LONG  32




static __always_inline int fls(int x)
{
	int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
}

#if BITS_PER_LONG == 32
static __always_inline int fls64(__u64 x)
{
	__u32 h = x >> 32;
	if (h)
		return fls(h) + 32;
	return fls(x);
}
#elif BITS_PER_LONG == 64
static __always_inline int fls64(__u64 x)
{
	if (x == 0)
		return 0;
	return __fls(x) + 1;
}
#endif




static inline unsigned fls_long(unsigned long l)
{
	if (sizeof(l) == 4)
		return fls(l);
	return fls64(l);
}


static inline __attribute__((const))
unsigned long is_power_of_2(unsigned long n)
{
	return (n != 0 && ((n & (n - 1)) == 0));
}

/*
 * round up to nearest power of two
 */
static inline __attribute__((const))
unsigned long __roundup_pow_of_two(unsigned long n)
{
	return 1UL << fls_long(n - 1);
}

/*
 * round down to nearest power of two
 */
static inline __attribute__((const))
unsigned long __rounddown_pow_of_two(unsigned long n)
{
	return 1UL << (fls_long(n) - 1);
}

/**
 * roundup_pow_of_two - round the given value up to nearest power of two
 * @n - parameter
 *
 * round the given value up to the nearest power of two
 * - the result is undefined when n == 0
 * - this can be used to initialise global variables from constant data
 */
#define roundup_pow_of_two(n)			\
(						\
	__builtin_constant_p(n) ? (		\
		(n == 1) ? 1 :			\
		(1UL << (ilog2((n) - 1) + 1))	\
				   ) :		\
	__roundup_pow_of_two(n)			\
 )

/**
 * rounddown_pow_of_two - round the given value down to nearest power of two
 * @n - parameter
 *
 * round the given value down to the nearest power of two
 * - the result is undefined when n == 0
 * - this can be used to initialise global variables from constant data
 */
#define rounddown_pow_of_two(n)			\
(						\
	__builtin_constant_p(n) ? (		\
		(1UL << ilog2(n))) :		\
	__rounddown_pow_of_two(n)		\
 )


#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })



#endif
