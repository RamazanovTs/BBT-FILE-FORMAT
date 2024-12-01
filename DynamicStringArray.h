#ifndef DYNAMIC_STRING_ARRAY_H
#define DYNAMIC_STRING_ARRAY_H

#include <stddef.h>

typedef struct {
  char **data;
  size_t size;
  size_t capacity;
} DynamicStringArray;

DynamicStringArray *CreateStringArray();

void freeStringArray(DynamicStringArray **array);

void expandStringArray(DynamicStringArray *array);

void addString(DynamicStringArray *array, const char *str);

void removeString(DynamicStringArray *array, size_t index);

const char *getString(DynamicStringArray *array, size_t index);

size_t getStringCount(DynamicStringArray *array);

#endif
