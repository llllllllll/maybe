#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "maybe.h"

NEW_MAYBE_TYPE(int);

static MAYBE(int)
f(int a)
{
    return (MAYBE(int)) just(a + 1);
}

int
main(int argc, char **argv)
{
    MAYBE(int) a = f(0);
    MAYBE(int) b = bind((MAYBE(int)) just(0), f);

    /* Check the left identity. */
    assert(!memcmp(&a, &b, sizeof(MAYBE(int))));
    assert(frommaybe(-1, a) == 1);  /* ensure the correct result. */

    /* Check the right identity. */
    a = bind((MAYBE(int)) just(1), UNIT(MAYBE(int)));
    b = (MAYBE(int)) just(1);

    assert(!memcmp(&a, &b, sizeof(MAYBE(int))));
    assert(frommaybe(-1, a) == 1);  /* ensure the correct result. */
    return 0;
}
