#ifndef SABR2_SABR_BUILTINS_H
#define SABR2_SABR_BUILTINS_H

#include "sabr_types.h"

/* sabr builtin functions */
/* these are NOT meant to be executed within C. */

void sabr_func_target(sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]);
sabr_function_t sabr_func_target_decl = {
        .name = "target",
        .min_args = 2,
        .func = sabr_func_target
};

void sabr_func_cc(sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]);
sabr_function_t sabr_func_cc_decl = {
        .name = "cc",
        .min_args = 1,
        .func = sabr_func_cc
};

void sabr_func_cc_options(sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]);
sabr_function_t sabr_func_cc_options_decl = {
        .name = "cc_options",
        .min_args = 1,
        .func = sabr_func_cc_options
};

#endif //SABR2_SABR_BUILTINS_H
