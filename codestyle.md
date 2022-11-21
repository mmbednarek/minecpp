# Error Handling

Handling errors is just as important as handling the happy path.
Therefore, we cannot rely on try/catch semantics. Instead, I implemented special
`result` and `error` class. (These classes do not follow the uppercase class name style, to resemble more the STL classes)
The result may contain a value or an error.

Example usage

```cpp
mb::result<double> div(double nom, double denom) {
    if (denom == 0) {
        return mb::error("cannot divide by zero");
    }
    return nom/denom;
}
```
