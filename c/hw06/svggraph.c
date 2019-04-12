#include "svggraph.h"
float plus(float value, struct function_struct *function)
{
    return value + function->constant;
}
float minus(float value, struct function_struct *function)
{
    return value - function->constant;
}
float cosinus(float value, struct function_struct *function)
{
    UNUSED(function);
    float result = cos(value);
    return result;
}
float sinus(float value, struct function_struct *function)
{
    UNUSED(function);
    float result = sin(value);
    return result;
}
float tangens(float value, struct function_struct *function)
{
    UNUSED(function);
    float result = tan(value);
    return result;
}
float mult(float value, struct function_struct *function)
{
    return function->constant * value;
}
float plusSVG(float value, struct function_struct *function)
{
    return ((value + function->constant * function->x_const) * function->y_const) / function->x_const;
}
float minusSVG(float value, struct function_struct *function)
{
    return ((value - function->constant * function->x_const) * function->y_const) / function->x_const;
}
float cosinusSVG(float value, struct function_struct *function)
{
    float result = cos(value / function->x_const) * function->x_const;
    return (result * function->y_const) / function->x_const;
}
float sinusSVG(float value, struct function_struct *function)
{
    float result = sin(value / function->x_const) * function->x_const;
    return (result * function->y_const) / function->x_const;
}
float tangensSVG(float value, struct function_struct *function)
{
    float result = tan(value / function->x_const) * function->x_const;
    return (result * function->y_const) / function->x_const;
}
float multSVG(float value, struct function_struct *function)
{
    return ((function->constant * value) * function->y_const) / function->x_const;
}
float round_correctly(float value) {
    return floorf(value * 100 + 0.5) / 100;
}
void initialize(struct function_struct *function)
{
    for (int i = 0; i < 6; i++) {
        function->x_array[i] = i;
        function->y_array[i] = 0;
        function->value_len[i] = 1;
    }
    function->file = NULL;
    function->operation = NULL;
    function->operation_len = 1;
    function->constant = 0;
    function->SVG = 0;
    function->width = 0;
    function->height = 0;
    function->x = 0;
    function->y = 0;
}
void initializeSVG(struct function_struct *function)
{
    function->info = 20;
    function->x_middle = floor((float)function->width / (float)2);
    function->y_middle = floor((float)function->height / (float)2);
    function->x_const = (float)function->width / (float)(2 * function->x);
    function->y_const = (float)function->height / (float)(2 * function->y);

    fprintf(function->file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(function->file, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
}
void initializeKartez(struct function_struct *function)
{
    // osy
    fprintf(function->file, "<line x1=\"0\" y1=\"%.0f\" x2=\"%d\" y2=\"%.0f\" style=\"stroke:rgb(100,100,100);stroke-width:3\"/>\n", function->y_middle, function->width, function->y_middle);
    fprintf(function->file, "<line x1=\"%.0f\" y1=\"0\" x2=\"%.0f\" y2=\"%d\" style=\"stroke:rgb(100,100,100);stroke-width:3\"/>\n", function->x_middle, function->x_middle, function->height);

    // cislovanie
    float start_x = -4;
    float start_y = function->height + 4;
    if (function->height % 2 == 0) {
        start_y += 1;
    }

    // x os
    for (int i = -function->x; i <= function->x; i++) {
        if (i == 0) {
            start_x += function->x_const;
            continue;
        }
        fprintf(function->file, "<text x=\"%.0f\" y=\"%.0f\" text-anchor=\"middle\" fill=\"black\">%d</text>\n", start_x, (function->y_middle - 2), i);
        start_x += function->x_const;
    }

    // y os
    for (int i = -function->y; i <= function->y; i++) {
        if (i == 0) {
            start_y -= function->y_const;
            continue;
        }
        fprintf(function->file, "<text x=\"%.0f\" y=\"%.0f\" fill=\"black\">%d</text>\n", (function->x_middle + 2), start_y, i);
        start_y -= function->y_const;
    }

    // 0
    fprintf(function->file, "<text x=\"%.0f\" y=\"%.0f\" fill=\"black\">%d</text>\n", (function->x_middle + 2), (function->y_middle - 2), 0);

    fprintf(function->file, "<defs>\n<clipPath id=\"myClip\">\n<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\"/>\n</clipPath>\n</defs>", function->width, function->height);
}
float convertToSVG(struct function_struct *function, float x, float y)
{
    float return_value;
    if ((x < 0 && y < 0) || (x > 0 && y < 0)) {
        return_value = function->y_middle + fabs(y);
        return return_value;
    }
    if ((x > 0 && y >= 0) || (x < 0 && y >= 0)) {
        return_value = function->y_middle - fabs(y);
        return return_value;
    }
    return_value = function->y_middle - y;
    return return_value;
}
void addPath(struct function_struct *function, float (*projector)(float, struct function_struct *))
{
    // farba
    int red = rand() % 200;
    int green = rand() % 200;
    int blue = rand() % 200;
    // text
    fprintf(function->file, "<text x=\"%d\" y=\"%d\" text-anchor=\"end\" font-size=\"18\" fill=\"rgb(%d,%d,%d)\">y = %s</text>", function->width - 2, function->info, red, green, blue, function->operation);
    function->info += 20;
    // path
    fprintf(function->file, "<path clip-path=\"url(#myClip)\" d=\"");
    int i = -1;
    for (int j = -function->x_middle; j <= function->x_middle; j++) {
        float value = convertToSVG(function, (float)j, projector((float)j, function));
        i += 1;
        if (i == 0) {
            fprintf(function->file, "M %d %.1f ", i, value);
            continue;
        }
        fprintf(function->file, "L %d %.1f ", i, value);
    }
    fprintf(function->file, "\" fill=\"transparent\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"1\"/>", red, green, blue);
}
void addPathTg(struct function_struct *function, float (*projector)(float, struct function_struct *))
{
    // farba
    int red = rand() % 200;
    int green = rand() % 200;
    int blue = rand() % 200;
    // text
    fprintf(function->file, "<text x=\"%d\" y=\"%d\" text-anchor=\"end\" font-size=\"18\" fill=\"rgb(%d,%d,%d)\">y = %s</text>", function->width - 2, function->info, red, green, blue, function->operation);
    function->info += 20;
    // path
    fprintf(function->file, "<path clip-path=\"url(#myClip)\" d=\"");
    int i = -1;
    float last = 0;
    for (int j = -function->x_middle; j <= function->x_middle; j++) {
        float value = convertToSVG(function, (float)j, projector((float)j, function));
        i += 1;
        if (i == 0) {
            fprintf(function->file, "M %d %.1f ", i, value);
            last = value;
            continue;
        }
        if (last < 0 && value > 0) {
            fprintf(function->file, "M %d %.1f ", i, value);
            last = value;
            continue;
        }
        fprintf(function->file, "L %d %.1f ", i, value);
        last = value;
    }
    fprintf(function->file, "\" fill=\"transparent\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"1\"/>", red, green, blue);
}
void printLine(struct function_struct *function)
{
    printf("+");
    for (int i = 0; i < function->operation_len; i++) {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < function->value_len[i]; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}
void printX(struct function_struct *function)
{
    printf("|");
    printf("%-*c", function->operation_len, 'x');
    printf("|");
    for (int i = 0; i < 6; i++) {
        printf("%-*g", function->value_len[i], function->x_array[i]);
        printf("|");
    }
    printf("\n");
}
void printY(struct function_struct *function)
{
    printf("|");
    printf("%s", function->operation);
    printf("|");
    for (int i = 0; i < 6; i++) {
        char tmp[20] = "";
        delete_zeros(function->y_array[i], tmp);
        printf("%s", tmp);
        printf("|");
    }
    printf("\n");
}
int printOutput(struct function_struct *function)
{
    printLine(function);
    printX(function);
    printLine(function);
    printY(function);
    printLine(function);
    return 1;
}

int linearControl(struct function_struct *function, char *string)
{
    /*------y = xexample....-------*/
    if (string[1] != ' ' || string[3] != ' ') {
        return 0;
    }
    /*------y = x example-------*/
    if (string[2] != '+' && string[2] != '-') {
        return 0;
    }
    /*------y = x + example-------*/
    if ((int)string[4] < 48 || (int)string[4] > 57) {
        return 0;
    }

    char enter = '0';
    sscanf(&string[4], "%f%c", &function->constant, &enter);
    /*------y = x + -5example....-------*/
    if (enter != '\n' || function->constant < 0) {
        return 0;
    }
    // vstup zaokruhlim
    function->constant = round_correctly(function->constant);
    // zistenie dlzky
    char tmp[20] = "";
    delete_zeros(function->constant, tmp);

    function->operation_len = strlen(tmp);
    return 1;

}
int multiplyControl(struct function_struct *function, char *string)
{
    char whitespace = '0';
    char x = '0';
    char enter = '0';

    sscanf(string, "%f%c%c%c", &function->constant, &whitespace, &x, &enter);

    /*------y = 5example....-------*/
    if (whitespace != ' ' || x != 'x' || enter != '\n') {
        return 0;
    }
    // vstup zaokruhlim
    function->constant = round_correctly(function->constant);
    // zistenie dlzky
    char tmp[20] = "";
    delete_zeros(function->constant, tmp);
    function->operation_len = strlen(tmp);
    return 1;
}
void delete_zeros(float number, char *tmp)
{
    sprintf(tmp, "%.2f", number);
    if (tmp[strlen(tmp) - 1] == '0') {
        if (tmp[strlen(tmp) - 2] == '0') {
            sprintf(tmp, "%.0f", number);
        } else {
            sprintf(tmp, "%.1f", number);
        }
    }
}
