#pragma once

#include <json-c/json.h>

#include "sudoku.h"

void fillTable(Table &, int);

char *tableToKey(AppState);

json_object *tableToJson(AppState);

bool isAvailable(AppState, int, int, int);

void fillRandom(AppState);

void freeTable(Table, int);