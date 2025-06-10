#include <cstdlib>

#include "sudoku.h"

typedef int **Table;

void fillTable(Table &table, int size) {
  table = new int*[size];
  for (int i = 0; i < size; i++) {
    table[i] = new int[size];
    for (int j = 0; j < size; j++) {
      table[i][j] = 0;
    }
  }
}

bool isAvailable(AppState state, int row, int col, int n) {
  // if is in the row/column
  for (int i = 0; i < state.size; i++) {
    if (state.table[row][i] == n || state.table[i][col] == n) return false;
  }

  int startRow = row - row % state.subSize;
  int startCol = col - col % 2;

  // if is in the subtable
  for (int i = 0; i < state.subSize; i++) {
    for (int j = 0; j < state.subSize; j++) {
      if (state.table[i + startRow][j + startCol] == n) return false;
    }
  }

  return true;
}

void fillRandom(AppState state) {
  for (int i = 0; i < state.size; i++) {
    for (int j = 0; j < state.size; j++) {
      int n = rand() % 10;
      if (rand() % 10 < state.size / 3 && isAvailable(state, i, j, n))
        state.table[i][j] = rand() % 10;
      else
        state.table[i][j] = 0;
    }
  }
}

void freeTable(Table table, int size) {
  for (int i = 0; i < size; i++) delete[] table[i];
  delete[] table;
}