#include "common.h"
/* Init function - initIntArray() - init int_segment
 *               - initCharArray() - init char_segment
 *               - initTimeArray() - init time_segment
 */
struct int_segment*returnIntArray(struct main_structure *structure, enum type enum_type)
{
    switch (enum_type) {
    case hard:
        return &structure->hard;
        break;
    case size:
        return &structure->size;
        break;
    case inode:
        return &structure->inode;
        break;
    default:
        return NULL;
        break;
    }
}

struct char_segment*returnCharArray(struct main_structure *structure, enum type enum_type)
{
    switch (enum_type) {
    case mode:
        return &structure->mode;
        break;
    case user_name:
        return &structure->user_name;
        break;
    case group_name:
        return &structure->group_name;
        break;
    case name:
        return &structure->name;
        break;
    case mod_time:
        return &structure->m_time;
        break;
    default:
        return NULL;
        break;
    }
}

int numberOfCharInInteger(size_t number)
{
    int numberofchar = 1;
    while ((number = number / 10) != 0) {
        numberofchar++;
    }
    return numberofchar;
}
int initIntArray(struct int_segment *segment, size_t constant)
{
    segment->multiple = 1;
    segment->index = 0;
    segment->len = 0;
    segment->array = malloc(constant * segment->multiple * sizeof(size_t));
    if (segment->array == NULL) {
        fprintf(stderr, "Heap Error");
        return 0;
    }
    return 1;
}
int initCharArray(struct char_segment *segment, size_t constant)
{
    segment->multiple = 1;
    segment->index = 0;
    segment->len = 0;
    segment->array = malloc(constant * segment->multiple * sizeof(char *));
    if (segment->array == NULL) {
        fprintf(stderr, "Heap Error");
        return 0;
    }
    return 1;
}
void freeIntArray(struct int_segment *segment)
{
    free(segment->array);
}
void freeCharArray(struct char_segment *segment)
{
    for (size_t i = 0; i < segment->index; i++) {
        free(segment->array[i]);
    }
    free(segment->array);
}
void freeWorkPlace(struct main_structure *structure, size_t index)
{
    size_t i = 0;
    while (i <= index) {
        if (structure->columns[i] == name) {
            i++;
            continue;
        }
        if ((structure->columns[i] == hard) || (structure->columns[i] == size) || (structure->columns[i] == inode)) {
            struct int_segment* segment = returnIntArray(structure, structure->columns[i]);
            freeIntArray(segment);
        } else {
            struct char_segment* segment = returnCharArray(structure, structure->columns[i]);
            freeCharArray(segment);
        }
        i++;
    }
}

int appendChar(struct char_segment *segment, size_t constant, char *name_file)
{
    if (segment->index >= constant * segment->multiple) {
        segment->multiple++;
        char **new_pointer = realloc(segment->array, sizeof(char *) * constant * segment->multiple);
        if (new_pointer == NULL) {
            fprintf(stderr, "Heap Error");
            return 0;
        }
        segment->array = new_pointer;
    }

    int len = strlen(name_file);
    if (len > segment->len) {
        segment->len = len;
    }
    segment->array[segment->index] = malloc((len * sizeof(char)) + 1);
    if (segment->array[segment->index] == NULL) {
        fprintf(stderr, "Heap Error");
        for (size_t i = 0; i < segment->index; i++) {
            free(segment->array[i]);
        }
        return 0;
    }
    strcpy(segment->array[segment->index], name_file);
    segment->index++;
    return 1;
}

int appendInt(struct int_segment *segment, size_t constant, size_t number)
{
    if (segment->index >= constant * segment->multiple) {
        segment->multiple++;
        size_t *new_pointer = realloc(segment->array, sizeof(size_t) * constant * segment->multiple);
        if (new_pointer == NULL) {
            fprintf(stderr, "Heap Error");
            return 0;
        }
        segment->array = new_pointer;
    }
    int len = numberOfCharInInteger(number);
    if (len > segment->len) {
        segment->len = len;
    }
    segment->array[segment->index] = number;
    segment->index++;
    return 1;
}

int initWorkPlace(struct main_structure *structure)
{
    size_t i = 0;
    while (i < structure->index_of_columns) {
        if (structure->columns[i] == name) {
            i++;
            continue;
        }
        if ((structure->columns[i] == hard) || (structure->columns[i] == size) || (structure->columns[i] == inode)) {
            struct int_segment* segment = returnIntArray(structure, structure->columns[i]);
            if (!initIntArray(segment, structure->constant)) {
                freeWorkPlace(structure, i - 1);
                return 0;
            }
        } else {
            struct char_segment* segment = returnCharArray(structure, structure->columns[i]);
            if (!initCharArray(segment, structure->constant)) {
                freeWorkPlace(structure, i - 1);
                return 0;
            }
        }
        i++;
    }
    return 1;
}
void mode_to_string(mode_t mode, char str[11])
{
    strcpy(str, "----------"); // 10 x -
    char *p = str;


    if (S_ISDIR(mode))
        *p = 'd';
    p++;

    // Owner

    if (mode & S_IRUSR)
        *p = 'r';
    p++;
    if (mode & S_IWUSR)
        *p = 'w';
    p++;
    if (mode & S_IXUSR)
        *p = 'x';
    p++;

    // Group

    if (mode & S_IRGRP)
        *p = 'r';
    p++;
    if (mode & S_IWGRP)
        *p = 'w';
    p++;
    if (mode & S_IXGRP)
        *p = 'x';
    p++;

    // Others

    if (mode & S_IROTH)
        *p = 'r';
    p++;
    if (mode & S_IWOTH)
        *p = 'w';
    p++;
    if (mode & S_IXOTH)
        *p = 'x';
    p++;

}
