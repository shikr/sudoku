#pragma once

constexpr double DELAY = 0.2;

typedef int **Table;

enum AppStatus { SizeSelecting, Selecting, Resolving, Finished };

typedef struct {
  Table table;
  AppStatus status;
  char *key;
  int size;
  int subSize;
  size_t step;
  double lastStepTime;
} AppState;