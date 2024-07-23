#include "sabr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* sabr builtin functions */

void sabr_func_target(sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]) {
    if (argc < descriptor->min_args) {
        sabr_print_error(line_info, ERR_NOT_ENOUGH_ARGS);
        sabr_project_free(project);
        exit(1);
    }


    project->targets[project->target_count] = malloc(sizeof(sabr_target_t));
    sabr_target_t *target = project->targets[project->target_count];

    target->name = strdup(argv[0]);
    target->source_file_count = 0;

    int i;
    for (i = 1; i < argc; i++) {
        if (i >= MAX_ARGUMENT_COUNT - 1) {
            sabr_print_error(line_info, ERR_TOO_MANY_ARGS);
            sabr_project_free(project);
            exit(1);
        }
        target->source_files[i - 1] = strdup(argv[i]);
        target->source_file_count++;
    }

    project->target_count++;
}

void sabr_func_cc(sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]) {
    if (argc < descriptor->min_args) {
        sabr_print_error(line_info, ERR_NOT_ENOUGH_ARGS);
        sabr_project_free(project);
        exit(1);
    }

    if (!strcmp(argv[0], "autodetect")) {
        sabr_print_error(line_info, "Compiler autodetect feature is coming soon.");
        sabr_project_free(project);
        exit(1);
    } else {
        project->compiler.binary = strdup(argv[0]);
    }
}

void sabr_func_cc_options(sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]) {
    if (argc < descriptor->min_args) {
        sabr_print_error(line_info, ERR_NOT_ENOUGH_ARGS);
        sabr_project_free(project);
        exit(1);
    }

    int i;
    for (i = 0; i < argc; i++) {
        project->compiler.options[i] = strdup(argv[i]);
        project->compiler.option_count++;
    }
}
