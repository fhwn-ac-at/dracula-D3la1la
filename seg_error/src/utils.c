#include <stdlib.h>
#include "utils.h"

int roll_die_uniform(int sides) {
    return (rand() % sides) + 1;
}
