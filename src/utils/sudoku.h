#pragma once

typedef int **Table;

enum AppStatus {
  SizeSelecting,
  Selecting,
  Resolving,
  Finished
};

typedef struct {
  Table table;
  AppStatus status;
  int size;
  int subSize;
} AppState;