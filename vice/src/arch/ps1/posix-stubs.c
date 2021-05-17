#include <stddef.h>

void *lib_malloc(size_t size) {}
void *lib_calloc(size_t a, size_t b) {}
void lib_free(void *ptr) {}
char * lib_strdup(const char * str) {}
void exit(int code) {}
char *strrchr(const char *str, int c) {}
int strcmp(const char *str1, const char *str2) {}
int strlen(const char *str) {}
char *strcpy(char *dest, const char *src) {}
char *strcat(char *dest, const char *src) {}
void *memset(void *dest, int c, size_t n) {}
void *memcpy(void *dest, const void *src, size_t n) {}

void log_message() {}
void log_warning() {}
void log_error() {}
