#include <string.h>
#include <stdlib.h>
#include "score.h"

int main(){
    printf("Content-type:text/html\n\n");
    FILE *f = NULL;
    afficherScore(f);
    return EXIT_SUCCESS;
}
