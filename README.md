# maybe


The maybe monad for c.

## Use case

Commonly we write function like:

```c
ssize_t
indexof(int v, int *vs, size_t len)
{
    size_t idx;

    for (idx = 0;idx < len;++idx) {
        if (v == vs[idx]) {
            return idx;
        }
    }
    return -1;
}

```

In this case, we have a codomain of `ssize_t`. This tells us that the return
type may be a positive or negative value. This contradicts the definiton of our
index of function, because a valid index is a non-negative number. In order to
provide room for another value of our function, the error case, we needed to
add a new value to the codomain.

What we really want is a way to generalize the idea of a set of values plus one
more value.

With `maybe` we could write this as:

```c

MAYBE(size_t)
indexof(int v, int *vs, size_t len)
{
    size_t idx;
    int h;

    for (idx = 0;idx < len;++idx) {
        if (v == vs[idx]) {
            return (MAYBE(size_t)) just(idx);
        }
    }
    return (MAYBE(size_t)) NOTHING;
}
```

## Why

What this means is that I cannot write code like this:


```c
arr[indexof(c, cs, clen)] = n;
```

Did you catch the error?

What if `c` is not in `cs`? The compiler happily let me continue on; however,
we would have failed when the failure case of `return -1` was hit. This would
potentially have caused a nasty bug; however, in the `maybe` version we get:

```
error: array subscript is not an integer
     cs[indexof(2, cs, 3)] = 4;
       ^
```

Because we forgot to explicitly cast back to `size_t`, we allowed the type
checker to indicate that we forgot to manage the failure case and we get this
error at compile time.
