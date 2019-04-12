#include "svggraph.h"

void countingResult(struct function_struct *function, float (*projector)(float, struct function_struct *))
{
    // pomocna premenna na zistenie dlzky cisla
    char tmp[20] = "";

    for (int i = 0; i < 6; i++) {
        // vypocet
        function->y_array[i] = projector(function->x_array[i], function);
        // zaokruhlenie na 2 desatinne miesta
        function->y_array[i] = round_correctly(function->y_array[i]);
        // zistenie dlzky cisla
        delete_zeros(function->y_array[i], tmp);
        function->value_len[i] = strlen(tmp);
    }
}

int goniometric(struct function_struct *function, char *string)
{
    function->operation = malloc(6 * sizeof(char));
    function->operation_len = 5;

    /*------y = cos x-------*/
    if (strcmp(string, "cos x\n") == 0) {
        // ulozenie operacie
        strcpy(function->operation, "cos x");
        // vypocet
        countingResult(function, cosinus);
        // SVG
        if (function->SVG) {
            addPath(function, cosinusSVG);
        }
        return 1;
    }
    /*------y = sin x-------*/
    if (strcmp(string, "sin x\n") == 0) {
        // ulozenie operacie
        strcpy(function->operation, "sin x");
        // vypocet
        countingResult(function, sinus);
        // SVG
        if (function->SVG) {
            addPath(function, sinusSVG);
        }
        return 1;
    }
    if (strcmp(string, "tg x\n") == 0) {
        function->operation_len = 4;
        // ulozenie operacie
        strcpy(function->operation, "tg x");
        // vypocet
        countingResult(function, tangens);
        // SVG
        if (function->SVG) {
            addPathTg(function, tangensSVG);
        }
        return 1;
    }
    free(function->operation);
    return 0;
}

int linear(struct function_struct *function, char *string)
{
    if (!linearControl(function, string)) {
        return 0;
    }

    function->operation = malloc((5 + function->operation_len) * sizeof(char));
    function->operation_len += 4;

    char tmp[20] = "";
    switch (string[2]) {
    case '+':
        // ulozenie operacie
        delete_zeros(function->constant, tmp);
        sprintf(function->operation, "x + %s", tmp);
        // vypocet
        countingResult(function, plus);
        // SVG
        if (function->SVG) {
            addPath(function, plusSVG);
        }
        return 1;
        break;
    case '-':
        // ulozenie operacie
        delete_zeros(function->constant, tmp);
        sprintf(function->operation, "x - %s", tmp);
        // vypocet
        countingResult(function, minus);
        // SVG
        if (function->SVG) {
            addPath(function, minusSVG);
        }
        return 1;
        break;
    default:
        free(function->operation);
        return 0;
    }
    return 1;
}

int multiply(struct function_struct *function, char *string)
{
    if (!multiplyControl(function, string)) {
        return 0;
    }

    function->operation = malloc((5 + function->operation_len) * sizeof(char));
    function->operation_len += 2;

    // ulozenie operacie
    char tmp[20] = "";
    delete_zeros(function->constant, tmp);
    sprintf(function->operation, "%s x", tmp);
    // vypocet
    countingResult(function, mult);
    // SVG
    if (function->SVG) {
        addPath(function, multSVG);
    }
    return 1;
}
int controlFunction(struct function_struct *function, char *string)
{
    /*------y = -------*/
    if (string[0] != 'y' || string[1] != ' ' || string[2] != '=' || string[3] != ' ') {
        return 0;
    }

    /*------X-------*/
    // rozdriedenie podla vstupu
    switch (string[4]) {

    /*------y = x....-------*/
    case 'x':
        if (!linear(function, &string[4])) {
            return 0;
        }
        break;
    /*------y = c....(cos)-------*/
    case 'c':
        if (!goniometric(function, &string[4])) {
            return 0;
        }
        break;
    /*------y = s....(sin)-------*/
    case 's':
        if (!goniometric(function, &string[4])) {
            return 0;
        }
        break;
    /*------y = t....(tg)-------*/
    case 't':
        if (!goniometric(function, &string[4])) {
            return 0;
        }
        break;
    default:
        /*------y = example....-------*/
        if (((int)string[4] < 48 || (int)string[4] > 57) && string[4] != '-') {
            return 0;
        }
        /*------y = 5....-------*/
        if (!multiply(function, &string[4])) {
            return 0;
        }
        break;
    }
    return 1;
}
int loadCommandLine(struct function_struct *function, char *argv[])
{
    function->file = fopen(argv[1], "w");
    if (function->file == NULL) {
        perror("Error");
        return 0;
    }
    for (size_t i = 2; i <= 5; i++) {
        for (size_t j = 0; j < strlen(argv[i]); j++) {
            if ((int)argv[i][j] < 48 || (int)argv[i][j] > 57) {
                fprintf(stderr, "Ivalid Input Parameters\n");
                fclose(function->file);
                return 0;
            }
        }
    }
    function->width = atoi(argv[2]);
    function->height = atoi(argv[3]);
    function->x = atoi(argv[4]);
    function->y = atoi(argv[5]);
    return 1;
}
int loadInput(struct function_struct *function)
{
    char string[20] = "";
    while (1) {
        printf("> ");
        fgets(string, 20, stdin);
        if (strcmp(string, "exit\n") == 0) {
            return 1;
        }
        if (!controlFunction(function, string)) {
            fprintf(stderr, "Bad function.\n");
        } else {
            printOutput(function);
            free(function->operation);
        }
    }
}

int main(int argc, char *argv[])
{
    struct function_struct function;
    // inicializacia struktury
    initialize(&function);

    // vypis
    if (argc == 1) {
        loadInput(&function);
        return 0;
    }

    // vypis + SVG
    if (argc == 6) {
        if (!loadCommandLine(&function, argv)) {
            return 1;
        }
        function.SVG = 1;
        initializeSVG(&function);
        initializeKartez(&function);
        loadInput(&function);
        fprintf(function.file, "\n</svg>");
        fclose(function.file);
        return 0;
    }
    if (argc != 6 && argc != 1) {
        fprintf(stderr, "Ivalid Input Parameters\n");
        return 1;
    }
    return 0;
}
