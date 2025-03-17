#include <stdlib.h>
#include <stdio.h>
#include <c_fms.h>
#include <c_horiz_interp.h>

int main()
{
    cFMS_init(NULL,NULL,NULL,NULL);

    cFMS_horiz_interp_init();

    cFMS_end();

    return EXIT_SUCCESS;
}

// void test_horiz_interp_conserve_new_2dx2d()
// {

// }