#pragma once

#include "sudoku.h"

void fillTable(Table &, int);

char *tableToKey(AppState);

bool isAvailable(AppState, int, int, int);

void fillRandom(AppState);

void freeTable(Table, int);