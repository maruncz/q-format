# Q-format

Templated fixed point aritmetics.

```
q<N,D> num;
```
- `N` - number of bits in front of decimal point including sign bit
- `D` - number of bits after decimal point

Underlying type is automatically selected based on `N` and `D`.
Basic operations (`+`, `-`, `*`, `/`) are working. complex operations in progress.
