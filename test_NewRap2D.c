#include "NewRap2D.h"

/* Testing framework */
#include "greatest.h"

TEST test_NewRap2D(void) {
    int x = 1;
    ASSERT_EQ(1, x);

    /* If we are here, we passed the test. */
    PASS();
}

/* Add all the definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization. */

    /* Standalone tests can appear before or after other suites. */
    RUN_TEST(test_NewRap2D);

    GREATEST_MAIN_END();        /* display results */
}
