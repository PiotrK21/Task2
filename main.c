#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Sig_analyze.h"
#include "Load_data.h"

int main()
{

    char* data = fun_load_data();               // load data from file

    bool result = fun_signal_analyze(data);     // run analyze

    free(data);

    system("pause");

    return 0;
}




