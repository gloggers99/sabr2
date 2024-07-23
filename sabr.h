#ifndef SABR2_SABR_H
#define SABR2_SABR_H

#include "sabr_types.h"

#include <stdint.h>

void sabr_register_functions(sabr_project_t *project);

sabr_project_t *sabr_project_load(const char *file);
void sabr_project_free(sabr_project_t *project);

void sabr_project_build(sabr_project_t *project);

void sabr_project_add_function(sabr_project_t *project, sabr_function_t *function);
void sabr_make_params(char *input, int *argc, char **argv);
void sabr_make_compiler_command(sabr_compiler_t compiler, char *buffer);

void sabr_print_error(sabr_line_info_t line_info, char *description);
void sabr_print_warning(sabr_line_info_t line_info, char *description);


#endif /* SABR2_SABR_H */
