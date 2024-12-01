#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    size_t size;
    size_t capacity;
} DynamicStringArray;

DynamicStringArray *CreateStringArray() {
    DynamicStringArray *array = malloc(sizeof(DynamicStringArray));
    if (!array) {
        printf("Error in memory allocation for DynamicStringArray!\n");
        return NULL;
    }

    array->size = 0;
    array->capacity = 4;

    array->data = malloc(sizeof(char *) * array->capacity);
    if (!array->data) {
        free(array);
        printf("Error in memory allocation for data!\n");
        return NULL;
    }
    return array;
}

void freeStringArray(DynamicStringArray **array) {
    if (array && *array) {
        for (size_t i = 0; i < (*array)->size; i++) {
            free((*array)->data[i]);
        }
        free((*array)->data);
        free(*array);
        *array = NULL;
    }
}

void expandStringArray(DynamicStringArray *array) {
    if (!array) {
        printf("Array not found in expandStringArray!\n");
        return;
    }

    size_t new_capacity = array->capacity * 2;
    char **new_data = realloc(array->data, sizeof(char *) * new_capacity);
    if (new_data) {
        array->data = new_data;
        array->capacity = new_capacity;
    } else {
        printf("Could not reallocate memory!\n");
    }
}

void addString(DynamicStringArray *array, const char *str) {
    if (!array) {
        printf("Array not found in addString!\n");
        return;
    }

    if (array->size == array->capacity) {
        expandStringArray(array);
    }

    if (array->size < array->capacity) {
        array->data[array->size] = strdup(str);
        if (!array->data[array->size]) {
            printf("Error duplicating string!\n");
            return;
        }
        array->size++;
    }
}

void removeString(DynamicStringArray *array, size_t index) {
    if (!array) {
        printf("Array not found in removeString!\n");
        return;
    }

    if (index < array->size) {
        free(array->data[index]);
        for (size_t i = index; i < array->size - 1; i++) {
            array->data[i] = array->data[i + 1];
        }
        array->size--;
    } else {
        printf("Invalid index %zu in removeString!\n", index);
    }
}

const char *getString(DynamicStringArray *array, size_t index) {
    if (!array) {
        printf("Array not found in getString!\n");
        return NULL;
    }

    if (index < array->size) {
        return array->data[index];
    } else {
        printf("Index %zu out of range in getString!\n", index);
        return NULL;
    }
}

size_t getStringCount(DynamicStringArray *array) {
    if (!array) {
        printf("Array not found in getStringCount!\n");
        return 0;
    }
    return array->size;
}
