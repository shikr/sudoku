#pragma once

inline constexpr int TABLE_SIZE = 9;

typedef int **Table;

enum AppStatus {
  Selecting,
  Resolving,
  Finished
};

typedef struct {
  Table table;
  AppStatus status;
} AppState;