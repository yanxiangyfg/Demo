#ifndef __ASM_GENERIC_BARRIER_H
#define __ASM_GENERIC_BARRIER_H

#ifndef __ASSEMBLY__

#define nop() asm volatile ("nop")

/*
 * Force strict CPU ordering.
 * And yes, this is required on UP too when we're talking
 * to devices.
 *
 * This implementation only contains a compiler barrier.
 */

#define mb()	__asm__ __volatile__("": : :"memory")
#define rmb()	mb()
#define wmb()	__asm__ __volatile__("": : :"memory")

/* Optimization barrier */
/* The "volatile" is due to gcc bugs */
#define barrier() __asm__ __volatile__("": : :"memory")


#if 0
#define smp_mb()	mb()
#define smp_rmb()	rmb()
#define smp_wmb()	wmb()
#else
#define smp_mb()	barrier()
#define smp_rmb()	barrier()
#define smp_wmb()	barrier()
#endif

#define set_mb(var, value)  do { var = value;  mb(); } while (0)
#define set_wmb(var, value) do { var = value; wmb(); } while (0)

#define read_barrier_depends()		do {} while (0)
#define smp_read_barrier_depends()	do {} while (0)

#endif /* !__ASSEMBLY__ */
#endif /* __ASM_GENERIC_BARRIER_H */

