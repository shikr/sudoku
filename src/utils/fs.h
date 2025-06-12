#pragma once

#include <json-c/json.h>

#include "sudoku.h"

char *getEnv(const char *);

void saveStep(AppState);

size_t getStepsSize(char *);

Table getStep(AppState);