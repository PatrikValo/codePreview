#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define UNUSED(x) (void)(x)

struct function_struct
{
    FILE *file;
    float x_array[6];
    float y_array[6];
    float constant;
    int value_len[6];
    char *operation;
    int operation_len;
    // SVG
    int SVG;
    int width;
    int height;
    int x;
    int y;
    float x_const;
    float y_const;
    float x_middle;
    float y_middle;
    int info;
};
float plus(float value, struct function_struct *function);
float minus(float value, struct function_struct *function);
float cosinus(float value, struct function_struct *function);
float sinus(float value, struct function_struct *function);
float tangens(float value, struct function_struct *function);
float mult(float value, struct function_struct *function);
float plusSVG(float value, struct function_struct *function);
float minusSVG(float value, struct function_struct *function);
float cosinusSVG(float value, struct function_struct *function);
float tangensSVG(float value, struct function_struct *function);
float sinusSVG(float value, struct function_struct *function);
float multSVG(float value, struct function_struct *function);
float round_correctly(float value);
void initialize(struct function_struct *function);
void initializeSVG(struct function_struct *function);
void initializeKartez(struct function_struct *function);
void addPath(struct function_struct *function, float (*projector)(float, struct function_struct *));
void addPathTg(struct function_struct *function, float (*projector)(float, struct function_struct *));
int printOutput(struct function_struct *function);
int linearControl(struct function_struct *function, char *string);
int multiplyControl(struct function_struct *function, char *string);
void delete_zeros(float number, char *tmp);
