#ifndef SABR2_SABR_BUILTINS_H
#define SABR2_SABR_BUILTINS_H

#include "sabr_types.h"

/* sabr builtin functions */
/* these are NOT meant to be executed within C. */

#define FUNCTION_ARGUMENTS sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]

void sabr_func_target(FUNCTION_ARGUMENTS);
sabr_function_t sabr_func_target_decl = {
        .name = "target",
        .min_args = 2,
        .func = sabr_func_target
};

void sabr_func_cc(FUNCTION_ARGUMENTS);
sabr_function_t sabr_func_cc_decl = {
        .name = "cc",
        .min_args = 1,
        .func = sabr_func_cc
};

void sabr_func_cc_options(FUNCTION_ARGUMENTS);
sabr_function_t sabr_func_cc_options_decl = {
        .name = "cc_options",
        .min_args = 1,
        .func = sabr_func_cc_options
};

void sabr_func_language(FUNCTION_ARGUMENTS);
sabr_function_t sabr_func_language_decl = {
        .name = "language",
        .min_args = 1,
        .func = sabr_func_language
};

/*
 * windows exclusive function to fetch compiler from a mingw toolchain
 */

#ifdef __WIN32
void sabr_func_mingw(sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]);
sabr_function_t sabr_func_mingw_decl = {
        .name = "mingw",
        .min_args = 1,
        .func = sabr_func_mingw
};
#endif

#endif /* SABR2_SABR_BUILTINS_H */
