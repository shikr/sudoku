#pragma once

#include "sudoku.h"

void fillTable(Table &, int);

bool isAvailable(AppState, int, int, int);

void freeTable(Table, int);