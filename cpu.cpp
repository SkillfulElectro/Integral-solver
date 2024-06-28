/*
to make this work with your custom type :
You have to Overload / , += , * and if needed = operators
*/

template <typename T>
T Integral(T (*expression)(T), T x1, T x2, T Accurate_level) {
    T distance = (x2 - x1) / Accurate_level;
    T sum = 0;

    for (; x1 < x2; x1 += distance) {
        sum += distance * expression(x1);
    }

    return sum;
}
