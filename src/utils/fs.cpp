#include <cstdlib>

char *getEnv(const char *var) {
  size_t len = 0;
  char *value;
  getenv_s(&len, nullptr, 0, var);
  if (len == 0) return NULL;
  value = new char[len];
  getenv_s(&len, value, len, var);
  return value;
}