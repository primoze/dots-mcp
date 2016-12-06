
#ifndef OS_BITS_H
#define OS_BITS_H

#include <os/common.h>
#include <avr/io.h>

namespace os {

/*
 * Get bit 'bit' of 't'.
 */
template <typename T>
OS_INLINE bool get_bit(T& t, byte_t bit);

template <typename T>
bool get_bit(T& t, byte_t bit) {
  return t & (T)_BV(bit);
}

/*
 * Set bit 'bit' of 't'.
 */
template <typename T>
OS_INLINE void set_bit(T& t, byte_t bit);

template <typename T>
void set_bit(T& t, byte_t bit) {
  t |= (T)_BV(bit);
}

/*
 * Mask 't' with 'mask' shifted by 'bit'
 */
template <typename T>
OS_INLINE void set_mask(T& t, const T& mask, byte_t bit);

template <typename T>
void set_mask(T& t, const T& mask, byte_t bit) {
  t |= (T)(mask << bit);
}


/*
 * Clear bit 'bit' of 't'.
 */
template <typename T>
OS_INLINE void clear_bit(T& t, byte_t bit);

template <typename T>
void clear_bit(T& t, byte_t bit) {
  t &= (T)~_BV(bit);
}

/*
 * Unmask 't' with 'mask' shifted by 'bit'
 */
template <typename T>
OS_INLINE void clear_mask(T& t, const T& mask, byte_t bit);

template <typename T>
void clear_mask(T& t, const T& mask, byte_t bit) {
	  t &= (T)~(mask << bit);
}

}




#endif // OS_BITS_H
