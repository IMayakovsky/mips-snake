#ifndef APPLE_H
#define APPLE_H

#include "point.h"

#define APPLES_MAX_SIZE 4

Point apples[APPLES_MAX_SIZE];

void init_apples();

void generate_new_apple(int i);

#endif //APPLE_H