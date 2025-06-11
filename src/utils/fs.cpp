#include <json-c/json.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include "sudoku.h"
#include "table.h"

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

void saveStep(AppState state) {
  char filename[] = "data.json";
  json_object *root =
      fs::exists(filename) ? json_object_from_file(filename) : json_object_new_object();
  json_object *array;

  if (!json_object_object_get_ex(root, state.key, &array)) {
    array = json_object_new_array();
    json_object_object_add(root, state.key, array);
  }

  json_object_array_add(array, tableToJson(state));

  json_object_to_file(filename, root);

  json_object_put(root);
}