#include "sabr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define FUNCTION_ARGUMENTS sabr_function_t *descriptor, sabr_line_info_t line_info, sabr_project_t *project, int argc, char *argv[]

/* sabr builtin functions */

void sabr_func_target(FUNCTION_ARGUMENTS) {
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

void sabr_func_cc(FUNCTION_ARGUMENTS) {
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

void sabr_func_cc_options(FUNCTION_ARGUMENTS) {
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

void sabr_func_language(FUNCTION_ARGUMENTS) {
    if (argc < descriptor->min_args) {
        sabr_print_error(line_info, ERR_NOT_ENOUGH_ARGS);
        sabr_project_free(project);
        exit(1);
    }

    if (!strcmp(argv[0], "c")) {
        project->compiler.language = C;
    } else if (!strcmp(argv[0], "c++") || !strcmp(argv[0], "cpp")) {
        project->compiler.language = CPP;
    } else {
        sabr_print_error(line_info, ERR_LANGUAGE_NOT_SUPPORTED);
    }
}

#ifdef __WIN32
void sabr_func_mingw(FUNCTION_ARGUMENTS) {
    if (argc < descriptor->min_args) {
        sabr_print_error(line_info, ERR_NOT_ENOUGH_ARGS);
        sabr_project_free(project);
        exit(1);
    }

    char *language_binary_target = strdup(argv[0]);
    strcat(language_binary_target, "/bin/");

    switch (project->compiler.language) {
        case C:
            strcat(language_binary_target, "cc");
            break;
        case CPP:
            strcat(language_binary_target, "c++");
            break;
        case UNSET:
            sabr_print_error(line_info, ERR_LANGUAGE_NOT_SET);
            sabr_project_free(project);
            exit(1);
    }

    strcat(language_binary_target, ".exe");

    struct stat buffer;
    if (stat(language_binary_target, &buffer)) {
        sabr_print_error(line_info, ERR_FILE_DOESNT_EXIST);
        sabr_project_free(project);
        exit(1);
    }

    project->compiler.binary = strdup(language_binary_target);
}
#endif
