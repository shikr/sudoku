#include <json-c/json.h>
#include <cstdlib>
#include <cstdio>
#include <filesystem>

#include "sudoku.h"

namespace fs = std::filesystem;

char *getEnv(const char *var) {
  size_t len = 0;
  char *value;
  getenv_s(&len, nullptr, 0, var);
  if (len == 0) return NULL;
  value = new char[len];
  getenv_s(&len, value, len, var);
  return value;
}

json_object *loadJson(AppState state) {
  char filename[] = "data.json";
  json_object *root = fs::exists(filename) ? json_object_from_file(filename) : json_object_new_object();
  char key[4];
  snprintf(key, 4, "%dx%d", state.size, state.size);
  json_object *table_map;
  json_object *array;

  if (!json_object_object_get_ex(root, key, &table_map)) {
    table_map = json_object_new_object();
    if (!json_object_object_get_ex(table_map, state.key, &array)) {
      array = json_object_new_array();
      json_object_object_add(table_map, state.key, array);
    }
    json_object_object_add(root, key, table_map);
  }

  json_object_to_file(filename, root);

  return root;
}