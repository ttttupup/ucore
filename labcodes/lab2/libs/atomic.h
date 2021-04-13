#ifndef __LIBS_ATOMIC_H__
#define __LIBS_ATOMIC_H__

/* Atomic operations that C can't guarantee us. Useful for resource counting etc.. */

static inline void set_bit(int nr, volatile void *addr) __attribute__((always_inline));
static inline void clear_bit(int nr, volatile void *addr) __attribute__((always_inline));
static inline void change_bit(int nr, volatile void *addr) __attribute__((always_inline));
static inline bool test_bit(int nr, volatile void *addr) __attribute__((always_inline));

/* *
 * set_bit - Atomically set a bit in memory
 * @nr:     the bit to set
 * @addr:   the address to start counting from
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 * */
static inline void
set_bit(int nr, volatile void *addr) {
    asm volatile ("btsl %1, %0" :"=m" (*(volatile long *)addr) : "Ir" (nr));   //位测试指令  将ADDR操作数中的第nr位（从0始）送CF，并且第nr位置1
}

/* *
 * clear_bit - Atomically clears a bit in memory
 * @nr:     the bit to clear
 * @addr:   the address to start counting from
 * */
static inline void
clear_bit(int nr, volatile void *addr) {
    asm volatile ("btrl %1, %0" :"=m" (*(volatile long *)addr) : "Ir" (nr));  //位测试并复位指令  将ADDR操作数中的第nr位（从0始）送CF，并且第nr位置0
}

/* *
 * change_bit - Atomically toggle a bit in memory
 * @nr:     the bit to change
 * @addr:   the address to start counting from
 * */
static inline void
change_bit(int nr, volatile void *addr) {
    asm volatile ("btcl %1, %0" :"=m" (*(volatile long *)addr) : "Ir" (nr)); //为操作数addr的第nr位送CF，然后将操作数的第nr位取反。
}

/* *
 * test_bit - Determine whether a bit is set
 * @nr:     the bit to test
 * @addr:   the address to count from
 * */
static inline bool
test_bit(int nr, volatile void *addr) {
    int oldbit;
    asm volatile ("btl %2, %1; sbbl %0,%0" : "=r" (oldbit) : "m" (*(volatile long *)addr), "Ir" (nr)); //sbb是带借位减法指令  指令格式：sbb 操作对象1，操作对象2  功能:操作对象1=操作对象1-操作对象2-CF   sbb ax,bx实现的功能是: (ax)=(ax)-(bx)-CF
    return oldbit != 0;
}

#endif /* !__LIBS_ATOMIC_H__ */

