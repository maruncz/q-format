#include "test_addition.h"
#include "test_division.h"
#include "test_doubleconversion.h"
#include "test_exp.h"
#include "test_limits.h"
#include "test_multiplications.h"
#include "test_root.h"
#include "test_separ.h"
#include "test_sizeconversion.h"
#include "test_subtraction.h"

int main(int /*argc*/, char * /*argv*/[])
{
    test_operations_addition();
    test_operations_addition17();
    test_operations_addition115();
    test_operations_addition131();
    return 0;
}
