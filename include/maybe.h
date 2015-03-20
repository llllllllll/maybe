#include "macro.h"

#ifndef MAYBE_MAYBE_H
#define MAYBE_MAYBE_H

/* Reference a maybe type. */
#define MAYBE(a) PASTE(__maybe_type_, a)

/* Returns the unit function for the given type.
   usage:
     just(MAYBE(int))(5) = M(5) */
#define UNIT(t) PASTE(__maybe_unit_, t)
#define JOIN(t) PASTE(__maybe_join, t)

/* A maybe type references an option type.
   The option is either a value of the original type, or NOTHING.
   For example, the set of elements in MAYBE(char) is:
   {just(n) | n in char} | {NOTHING} */
#define NEW_MAYBE_TYPE(a)                                               \
    typedef struct{                                                     \
        a __value;                                                      \
        unsigned char __isjust;                                         \
    }MAYBE(a);                                                          \
    MAYBE(a) UNIT(MAYBE(a))(a v) { return (MAYBE(a)) just(v); }

/* typedef statement for maybe types. */
#define TYPEDEF_MAYBE(a, b) typedef MAYBE(a) MAYBE(b)

/* Represents an empty object. */
#define NOTHING {.__value=0, .__isjust=0}

/* Maps an object into the MAYBE(typeof(v)) space. Monad unit. */
#define just(v) {.__value=(v), .__isjust=1}

/* Check if an object is a just value. */
#define isjust(m) ((m).__isjust)

/* Check if an object is NOTHING. */
#define isnothing(m) (!(m).__isjust)

/* A mapping MAYBE(a) -> a.
   default_ is a default value to use when m is NOTHING. */
#define frommaybe(default_, m)                                           \
    ({                                                                   \
        typeof(m) __maybe_frommaybe_tmp = (m);                           \
        (__maybe_frommaybe_tmp.__isjust) ? __maybe_frommaybe_tmp.__value \
            : default_;                                                  \
    })

/* A mapping from (a -> a) -> (MAYBE(a) -> MAYBE(a)).
   Maps f into the maybe value m.
   If m is NOTHING, then this returns NOTHING, otherwise, if m is JUST(v)
   then this returns JUST(f(v)). */
#define fmap(f, m) \
    ({                                                                  \
        typeof(m) __maybe_fmap_tmp = (m);                               \
        if (__maybe_fmap_tmp.__isjust) {                                \
            __maybe_fmap_tmp.__value =                                  \
                (typeof(__maybe_fmap_tmp.__value)) f(m.__value);        \
        }                                                               \
        __maybe_fmap_tmp;                                               \
    })

/* Monad join for m:
   just(just(v)) = just(v),
   just(NOTHING) = NOTHING,
   NOTHING = NOTHING */
#define join(m)                                                         \
    ({                                                                  \
        typeof(m) __maybe_join_tmp = (m);                               \
        /* Type check that this is of type M(M(a)). */                  \
        __maybe_join_tmp.__value.__isjust;                              \
        frommaybe((typeof(m)) NOTHING, __maybe_join_tmp);               \
    })


#define bind(m, f)                              \
    ({                                                                  \
        typeof(m) __maybe_bind_tmp = (m);                               \
        if (__maybe_bind_tmp.__isjust) {                                \
            __maybe_bind_tmp = (typeof(__maybe_bind_tmp)) f(m.__value); \
        }                                                               \
        __maybe_bind_tmp;                                               \
    })
#endif
