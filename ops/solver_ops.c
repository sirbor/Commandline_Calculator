#include "ops/solver_ops.h"
#include <string.h>

CalculationResult solver_matrix_det2x2(double m[2][2]) {
    CalculationResult res;
    res.value = (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}
