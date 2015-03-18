/* Reference a maybe type. */
#define MAYBE(a) __maybe_ ## a

/* A maybe type references an option type.
   The option is either a value of the original type, or NOTHING.
   For example, the set of elements in MAYBE(char) is:
   {just(n) | n in char} | {NOTHING} */
#define NEW_MAYBE_TYPE(a) typedef struct{       \
        unsigned char __isjust;                 \
        a __value;                              \
    }MAYBE(a)


/* Represents an empty object. */
#define NOTHING {0, 0}

/* Maps an object into the MAYBE(typeof(v)) space. */
#define JUST(v) {1, v}

/* Check if an object is a just value. */
#define isjust(m) (m.__isjust)

/* Check if an object is NOTHING. */
#define isnothing(m) (!m.__isjust)

/* A mapping MAYBE(a) -> a.
   default_ is a default value to use when m is NOTHING. */
#define frommaybe(default_, m) ((m.__isjust) ? m.__value : default_)

/* A mapping from (a -> a) -> (MAYBE(a) -> MAYBE(a)).
   Maps f into the maybe value m.
   If m is NOTHING, then this returns NOTHING, otherwise, if m is JUST(v)
   then this returns JUST(f(v)). */
#define fmap(f, m) ({                                             \
            typeof(m) __maybe_fmap_tmp = m;                     \
            if (isjust(m)) {                                    \
                __maybe_fmap_tmp.__value = f(m.__value);        \
            }                                                   \
            __maybe_fmap_tmp;                                   \
        })
