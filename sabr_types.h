#ifndef SABR2_SABR_TYPES_H
#define SABR2_SABR_TYPES_H

#include <stdint.h>

#define MAX_LEN 256

#define MAX_SOURCE_FILE_COUNT 256
#define MAX_TARGET_COUNT 256
#define MAX_FUNCTION_COUNT 256
#define MAX_ARGUMENT_COUNT 256
#define MAX_COMPILER_OPTION_COUNT 256

#define ERR_NOT_ENOUGH_ARGS "Not enough arguments passed to function."
#define ERR_TOO_MANY_ARGS "Argument count surpasses MAX_ARGUMENT_COUNT."

typedef struct {
    char *binary;

    size_t option_count;
    char *options[MAX_ARGUMENT_COUNT];
} sabr_compiler_t;

typedef struct {
    int line_number;
    char *line;
} sabr_line_info_t;

typedef struct {
    char *name;

    size_t source_file_count;
    char *source_files[MAX_SOURCE_FILE_COUNT];
} sabr_target_t;

/* predeclaration so we can access this in sabr_project_t and have a sabr_project_t pointer in the sabr_function_t */
typedef struct sabr_function sabr_function_t;

typedef struct {
    sabr_compiler_t compiler;

    size_t target_count;
    sabr_target_t *targets[MAX_TARGET_COUNT];

    size_t function_count;
    sabr_function_t *functions[MAX_FUNCTION_COUNT];
} sabr_project_t;

typedef struct sabr_function {
    char *name;
    int min_args;
    void (*func)(struct sabr_function*, sabr_line_info_t, sabr_project_t*, int, char**);
} sabr_function_t;


#endif //SABR2_SABR_TYPES_H
