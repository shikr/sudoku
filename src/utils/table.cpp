#include "sudoku.h"

typedef int **Table;

void fillTable(Table &table) {
  table = new int*[TABLE_SIZE];
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i] = new int[TABLE_SIZE];
    for (int j = 0; j < TABLE_SIZE; j++) {
      table[i][j] = 0;
    }
  }
}

void freeTable(Table table) {
  for (int i = 0; i < TABLE_SIZE; i++) delete[] table[i];
  delete[] table;
}