/*
you have to define function with name COMPARE_TYPENAME for 
your preferred type
*/

// Macro to define basic arithmetic operations for a type
#define DEFINE_OPERATIONS(TYPE) \
    TYPE add_##TYPE(TYPE a, TYPE b) { return a + b; } \
    TYPE minus_##TYPE(TYPE a, TYPE b) { return a - b; } \
    TYPE mul_##TYPE(TYPE a, TYPE b) { return a * b; } \
    TYPE div_##TYPE(TYPE a, TYPE b) { return a / b; }

// Macro to register standard arithmetic operations for a type
#define REGISTER_TYPE_OPERATIONS(TYPE, ZERO) \
    TYPE ADD_##TYPE(TYPE a, TYPE b) { return add_##TYPE(a, b); } \
    TYPE MINUS_##TYPE(TYPE a, TYPE b) { return minus_##TYPE(a, b); } \
    TYPE MUL_##TYPE(TYPE a, TYPE b) { return mul_##TYPE(a, b); } \
    TYPE DIV_##TYPE(TYPE a, TYPE b) { return div_##TYPE(a, b); } \
    const TYPE ZERO_##TYPE = ZERO;

// Macro to register custom arithmetic operations for a type
#define REGISTER_CUSTOM_TYPE_FUNCTIONS(TYPE, ADD_FUNC, MINUS_FUNC, MUL_FUNC, DIV_FUNC, ZERO) \
    TYPE ADD_##TYPE(TYPE a, TYPE b) { return ADD_FUNC(a, b); } \
    TYPE MINUS_##TYPE(TYPE a, TYPE b) { return MINUS_FUNC(a, b); } \
    TYPE MUL_##TYPE(TYPE a, TYPE b) { return MUL_FUNC(a, b); } \
    TYPE DIV_##TYPE(TYPE a, TYPE b) { return DIV_FUNC(a, b); } \
    const TYPE ZERO_##TYPE = ZERO;

// Macro to define the integral function for a type
#define DEFINE_INTEGRAL_FUNCTION(TYPE) \
    TYPE Integral_##TYPE(TYPE (*expression)(TYPE), TYPE x1, TYPE x2, TYPE Accurate_level) { \
        TYPE distance = DIV_##TYPE((MINUS_##TYPE(x2, x1)), Accurate_level); \
        TYPE sum = ZERO_##TYPE; \
        for (TYPE i = x1; COMPARE_##TYPE(i, x2); i = ADD_##TYPE(i, distance)) { \
            TYPE term = i; \
            TYPE expr = expression(term); \
            expr = MUL_##TYPE(expr, distance); \
            sum = ADD_##TYPE(sum, expr); \
        } \
        return sum; \
    }
