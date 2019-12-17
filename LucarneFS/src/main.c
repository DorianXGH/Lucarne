#include "../headers/lucarnefs.h"
#include "../headers/tests.h"
#include <string.h>

int main(int argc, char * argv[])
{
    switch (argc) {
        case 2:
            if (strcmp(argv[1], "--tests") == 0) {
                test_sizes();
            }
            break;

        default:
            break;
    }
    return 0;
}
