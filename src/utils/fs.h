#pragma once

#include <json-c/json.h>

#include "sudoku.h"

char *getEnv(const char*);

json_object *loadJson(AppState);