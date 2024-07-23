#include "sabr.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "sabr_builtins.h"

void sabr_register_functions(sabr_project_t *project) {
    sabr_project_add_function(project, &sabr_func_target_decl);
    sabr_project_add_function(project, &sabr_func_cc_decl);
    sabr_project_add_function(project, &sabr_func_cc_options_decl);
}

/* creation of sabr_project_t */

sabr_project_t *sabr_project_load(const char *file) {
    FILE *handle = fopen(file, "r");
    if (!handle) {
        fprintf(stderr, "sabr: Failed to open \"%s\"\n", file);
        return NULL;
    }

    sabr_project_t *project = malloc(sizeof(sabr_project_t));

    project->compiler.binary = NULL;
    project->compiler.option_count = 0;

    project->target_count = 0;
    project->function_count = 0;

    sabr_register_functions(project);

    int line = 1;
    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, handle)) {
        char function_name[MAX_LEN];
        char *function_parameters_tmp = malloc(MAX_LEN * sizeof(char));
        sscanf(buffer, "%[^(]%[^)]", function_name, function_parameters_tmp);
        char *function_parameters = function_parameters_tmp + 1;

        int function_argc;
        char *function_argv[MAX_ARGUMENT_COUNT];

        sabr_make_params(function_parameters, &function_argc, function_argv);

        sabr_line_info_t line_info = {
                line,
                buffer
        };

        size_t i;
        for (i = 0; i < project->function_count; i++) {
            if (project->functions[i]) {
                if (!strcmp(project->functions[i]->name, function_name)) {
                    project->functions[i]->func(project->functions[i], line_info, project, function_argc, function_argv);
                }
            }
        }

        free(function_parameters_tmp);

        line++;
    }

    fclose(handle);

    return project;
}

void sabr_project_free(sabr_project_t *project) {
    if (!project)
        return;

    size_t i;
    for (i = 0; i < project->target_count; i++) {
        if (project->targets[i])
            free(project->targets[i]);
    }

    free(project);
}

/* function helpers */

void sabr_project_add_function(sabr_project_t *project, sabr_function_t *function) {
    if (!project || !function)
        return;

    project->functions[project->function_count] = function;
    project->function_count++;
}

void sabr_make_params(char *input, int *argc, char **argv) {
    if (!input || !argc || !argv)
        return;

    *argc = 0;

    char *token = strtok(input, " ");
    while (token != NULL) {
        argv[*argc] = token;
        (*argc)++;
        token = strtok(NULL, " ");
    }
}

void sabr_print_error(sabr_line_info_t line_info, char *description) {
    fprintf(stderr, "Error:\non line %i: %s\ndescription:\n\t%s\n", line_info.line_number, line_info.line, description);
}

void sabr_print_warning(sabr_line_info_t line_info, char *description) {
    fprintf(stderr, "Warning:\non line %i: %s\ndescription:\n\t%s\n", line_info.line_number, line_info.line, description);
}
