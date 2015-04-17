#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

#include "maybe/macro.h"
#include "maybe.h"

#ifndef MAYBE_TYPES_H
#define MAYBE_TYPES_H

#define PTR(a) PASTE(__maybe_typemod_ptr_a)

#define CONST(a) PASTE(__maybe_typemod_const_, a)
#define SIGNED(a) PASTE(__maybe_typemod_signed_, a)
#define UNSIGNED(a) PASTE(__maybe_typemod_unsigned_, a)
#define VOLATILE(a) PASTE(__maybe_typemod_volatile_, a)
#define REGISTER(a) PASTE(__maybe_typemod_register_, a)
#define RESTRICT(a) PASTE(__maybe_typemod_restrict_, a)

#define _TYPE_EXPAND(a)                                 \
    typedef a* PTR(a);                                  \
    NEW_MAYBE_TYPE(PTR(A));                             \
    typedef const a CONST(a);                           \
    NEW_MAYBE_TYPE(CONST(a));                           \
    typedef const a* PTR(CONST(a));                     \
    NEW_MAYBE_TYPE(PTR(CONST(A));                       \
    typedef volatile a VOLATILE(a);                     \
    NEW_MAYBE_TYPE(VOLATILE(a));                        \
    typedef volatile a* PTR(VOLATILE(a));               \
    NEW_MAYBE_TYPE(PTR(VOLATILE(a)));                   \
    typedef register a REGISTER(a);                     \
    NEW_MAYBE_TYPE(REGISTER(a));                        \
    typedef register a* PTR(REGISTER(a));               \
    NEW_MAYBE_TYPE(PTR(REGISTER(a)));                   \
    typedef restrict a RESTRICT(a);                     \
    NEW_MAYBE_TYPE(RESTRICT(a));                        \
    typedef restrict a* PTR(RESTRICT(a));               \
    NEW_MAYBE_TYPE(PTR(RESTRICT(a)))

#define _SIGNED_EXPAND(a)                               \
    typedef signed a SIGNED(a);                         \
    NEW_MAYBE_TYPE(SIGNED(a));                          \
    typedef signed a* PTR(SIGNED(a));                   \
    NEW_MAYBE_TYPE(PTR(SIGNED(a)));                     \
    typedef unsigned a UNSIGNED(a);                     \
    NEW_MAYBE_TYPE(UNSIGNED(a));                        \
    typedef unsigned a* PTR(UNSIGNED(a));               \
    NEW_MAYBE_TYPE(PTR(UNSIGNED(a)));                   \
    typedef const signed a CONST(SIGNED(a));            \
    NEW_MAYBE_TYPE(CONST(SIGNED(a));                    \
    typedef const signed a* PTR(CONST(SIGNED(a)));      \
    NEW_MAYBE_TYPE(PTR(CONST(SIGNED(a))));              \
    typedef const unsigned a CONST(UNSIGNED(a));        \
    NEW_MAYBE_TYPE(CONST(UNSIGNED(a)));                 \
    typedef const unsigned a* PTR(CONST(UNSIGNED(a)));  \
    NEW_MAYBE_TYPE(PTR(CONST(UNSIGNED(a))))


typedef long long long_long;

/* default */
_TYPE_EXPAND(char);
_SIGNED_EXPAND(char);
_TYPE_EXPAND(short);
_SIGNED_EXPAND(short);
_TYPE_EXPAND(int);
_SIGNED_EXPAND(int);
_TYPE_EXPAND(long);
_SIGNED_EXPAND(long);
_TYPE_EXPAND(long_long);
_SIGNED_EXPAND(long_long);

_TYPE_EXPAND(size_t);
_TYPE_EXPAND(ssize_t);

/* inttypes.h */
_TYPE_EXPAND(imaxdiv_t);
_TYPE_EXPAND(wchar_t);

/* stdint.h */

_TYPE_EXPAND(int8_t);
_TYPE_EXPAND(int16_t);
_TYPE_EXPAND(int32_t);
_TYPE_EXPAND(int64_t);
_TYPE_EXPAND(uint8_t);
_TYPE_EXPAND(uint16_t);
_TYPE_EXPAND(uint32_t);
_TYPE_EXPAND(uint64_t);

#endif
