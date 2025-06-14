#include <json-c/json.h>

#include <cstdio>
#include <cstdlib>

#include "fs.h"
#include "sudoku.h"

typedef int **Table;

void fillTable(Table &table, int size) {
  table = new int *[size];
  for (int i = 0; i < size; i++) {
    table[i] = new int[size];
    for (int j = 0; j < size; j++) {
      table[i][j] = 0;
    }
  }
}

char *tableToKey(AppState state) {
  size_t size = state.size * state.size + state.size + 1;
  char *result = new char[size];
  result[0] = '\0';
  for (int i = 0; i < state.size; i++) {
    for (int j = 0; j < state.size; j++) {
      if (state.table[i][j] == 0) {
        snprintf(result, size, "%s%s", result, " ");
      } else {
        snprintf(result, size, "%s%d", result, state.table[i][j]);
      }
    }
    snprintf(result, size, "%s>", result);
  }
  return result;
}

json_object *tableToJson(AppState state) {
  json_object *arr = json_object_new_array();
  for (int i = 0; i < state.size; i++) {
    json_object *row = json_object_new_array();
    for (int j = 0; j < state.size; j++) {
      json_object_array_add(row, json_object_new_int(state.table[i][j]));
    }
    json_object_array_add(arr, row);
  }
  return arr;
}

bool isAvailable(AppState state, int row, int col, int n) {
  // if is in the row/column
  for (int i = 0; i < state.size; i++) {
    if (col != i && state.table[row][i] == n) return false;
    if (row != i && state.table[i][col] == n) return false;
  }

  int startRow = row - row % state.subSize;
  int startCol = col - col % state.subSize;

  // if is in the subtable
  for (int i = 0; i < state.subSize; i++) {
    if (i + startRow == row) continue;
    for (int j = 0; j < state.subSize; j++) {
      if (j + startCol == col) continue;
      if (state.table[i + startRow][j + startCol] == n) return false;
    }
  }

  return true;
}

bool checkTable(AppState state) {
  for (int i = 0; i < state.size; i++) {
    for (int j = 0; j < state.size; j++) {
      if (state.table[i][j] != 0) {
        if (!isAvailable(state, i, j, state.table[i][j])) return false;
      }
    }
  }
  return true;
}

bool findEmpty(AppState state, int &row, int &col) {
  for (row = 0; row < state.size; row++) {
    for (col = 0; col < state.size; col++) {
      if (state.table[row][col] == 0) return true;
    }
  }
  return false;
}

bool solve(AppState state) {
  int row, col;

  if (!findEmpty(state, row, col)) return true;

  for (int n = 1; n <= state.size; n++) {
    if (isAvailable(state, row, col, n)) {
      state.table[row][col] = n;

      saveStep(state);

      if (solve(state)) return true;

      state.table[row][col] = 0;  // Backtrack
    }
  }

  return false;
}

void fillRandom(AppState state) {
  for (int i = 0; i < state.size; i++) {
    for (int j = 0; j < state.size; j++) {
      int n = rand() % state.size + 1;
      if (rand() % 10 < state.size / 2 && isAvailable(state, i, j, n))
        state.table[i][j] = n;
      else
        state.table[i][j] = 0;
    }
  }
}

void freeTable(Table table, int size) {
  for (int i = 0; i < size; i++) delete[] table[i];
  delete[] table;
}