#include "sabr.h"

#include <stdio.h>

int main(void) {
    sabr_project_t *project = sabr_project_load("build.sabr");
    sabr_project_free(project);

    return 0;
}
