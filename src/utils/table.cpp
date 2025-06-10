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

void freeTable(Table table, int size) {
  for (int i = 0; i < size; i++) delete[] table[i];
  delete[] table;
}