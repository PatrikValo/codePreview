#include <ctype.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/* enum type - udrzujem si typ "stlpca"*/
enum hide_param
{
    ls,
    A,
    a
};
enum type
{
    mode,
    hard,
    user_name,
    group_name,
    size,
    mod_time,
    name,
    inode
};

/* struct char_segment - struktura pre slpce, ktore vypisuju char
 * array - udrzujem si pole stringov
 * index - pomocny index pre mazanie alokovanej pamate a pre vlakanie na prislusnu
 * poziciu
 * multiple - pomocna premenna pre malloc
 * len - premenna, ktora udrzuje pocet znakov stringu - pre vypis
 */
struct char_segment
{
    char **array;
    size_t index;
    size_t multiple;
    int len;
};

/* struct int_segment - to iste ako char_segment, akurat si udrzujem pole cisel*/
struct int_segment
{
    size_t *array;
    size_t index;
    size_t multiple;
    int len;
};

/* main_structure == hlavna struktura programu
 * constant - premenna pre malloc
 * current_dir - udryujem si handle na aktualny adresar
 * columns - informacie o stlpcoch - co chcem vypisovat
 * index_of_columns - pozicia v ramci colums
 * nasledovne struktury - reprezentacia stlpcov pomocov poli
 * hide - inofrmacia o tom, ci nacitat ".", "..", skryte subory - a == vypisujem vsetko
 *                                                                ls == nevypisujem skryte subory ani ".", ".."
 *                                                                A == vypisujem vsetko az na ".", ".."
 */
struct main_structure
{
    size_t constant;
    DIR *current_dir;
    size_t index_of_columns;
    enum type columns[8];
    struct char_segment mode;
    struct int_segment hard;
    struct char_segment user_name;
    struct char_segment group_name;
    struct int_segment size;
    struct char_segment m_time;
    struct char_segment name;
    struct int_segment inode;
    enum hide_param hide;
};

/* numberOfCharInInteger - funkcia na vyratanie poctu znakov cisla*/
struct int_segment*returnIntArray(struct main_structure *structure, enum type enum_type);
struct char_segment*returnCharArray(struct main_structure *structure, enum type enum_type);
int numberOfCharInInteger(size_t number);

/* Init functions - initIntArray() - inicializacia int_segment
 *                - initCharArray() - inicializacia char_segment
 */
int initIntArray(struct int_segment *segment, size_t constant);
int initCharArray(struct char_segment *segment, size_t constant);

/* Free functions - freeIntArray() - uvolnujem pamat pola integerov
 *                - freeCharArray() - uvolnujem pamat stringov
 *                - freeWorkPlace() - uvolnujem vsetku naalokovanu pamat
 */
void freeIntArray(struct int_segment *segment);
void freeCharArray(struct char_segment *segment);
void freeWorkPlace(struct main_structure *structure, size_t index);
int appendChar(struct char_segment *segment, size_t constant, char *name_file);
int appendInt(struct int_segment *segment, size_t constant, size_t number);
int initWorkPlace(struct main_structure *structure);
void mode_to_string(mode_t mode, char str[11]);
