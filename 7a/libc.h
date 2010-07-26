#pragma once

typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

typedef void FILE;

#define snprintf _snprintf

int printf(const char *, ...);
int snprintf(char *, int, const char *, ...);
int fprintf(FILE *, const char *, ...);
FILE *fopen(const char *, const char *);
int fclose(FILE *);
int fread(void *, int, int, FILE *);
int fwrite(const void *, int, int, FILE *);
int fseek(FILE *, int, int);
int fgetc(FILE *);
int strcmp(const char *, const char *);
char *strncpy(char *, const char *, int);
char *strncat(char *, const char *, int);
void *memset(void *, int, int);
