#include <stdlib.h>
#include <stdio.h>

//***********************************************
//              IMPORTANT NOTICE                *
//***********************************************
//  If you need to add more headers, which      *
//  you CAN, add them AFTER THIS LINE           *

//  but BEFORE the following one:               *
#include "memoryVM.h"
//  otherwise your code MAY FAIL TO COMPILE!    *
//                                              *
//  You have been warned.                       *
//***********************************************


// Here goes your glorious implementation.

/*----Structures----*/
enum type_of_sector
{
    common,
    father,
    child
};
/* pointer - ukazuje na alokovanu pamat - ak nejde o 2D array
 * reference - pocitadlo referencii
 * type - tu si ukladam info o type pamate - napr. vonkajsie, vnutorne pole, "obycajna pamat"
 * pointer2D - ukazuje na alokovane 2D pole
 * length - v pripade 2D pola - uchovava informaciu o pocte vnutornych poli - tuto informaciu
 * si udrzuje aj vonkajsie pole, ale aj podpolia
 * myfather - vyuziva sa len na podpoliach - ukazuje na vonkajsie pole - vyuzitie - pri volani
 * release a pri klesnuti reference na 0, skacem na myfather.pointer2D a mazem ukazovatel aby
 * nedoslo k dealokacii uz neexistujucej pamate
 */
struct sector
{
    void *pointer;
    int reference;
    enum type_of_sector type;
    void **pointer2D;
    int length;
    struct sector *myfather;
};

typedef struct array_of_sectors
{
    int constant;
    int multiple;
    int index;
    struct sector *array;
} memory_t;

memory_t structure;

/*----Code----*/

// control_overflow() - kontroluje pretecenie naalokovanej pamete --> realloc
bool control_overflow(void)
{
    ++structure.index;
    if (structure.index >= (structure.constant * structure.multiple)) {
        ++structure.multiple;
        struct sector *new_pointer = realloc(structure.array, structure.multiple * structure.constant * sizeof(struct sector));
        if (new_pointer == NULL) {
            --structure.index;
            --structure.multiple;
            return false;
        } else {
            structure.array = new_pointer;
        }
    }
    return true;
}

// initVM() - podla zadania
bool initVM(void)
{
    structure.constant = 5;
    structure.multiple = 1;
    structure.index = -1;
    structure.array = malloc(structure.constant * structure.multiple * sizeof(struct sector));
    if (structure.array == NULL) {
        return false;
    }
    return true;
}

// clearVM() - podla zadania - v mojom pripade, dealokuje globalnu strukturu
void clearVM(void)
{
    free(structure.array);
    structure.array = NULL;
}

// allocate() - podla zadania + inicializujem premenne, ktore potrebujem
void *allocate(size_t size)
{
    if (control_overflow()) {
        structure.array[structure.index].pointer = calloc(size, 1);
        if (structure.array[structure.index].pointer == NULL) {
            --structure.index;
            return NULL;
        }
        structure.array[structure.index].reference = 1;
        structure.array[structure.index].type = common;
        structure.array[structure.index].myfather = NULL;
        return structure.array[structure.index].pointer;
    }
    return NULL;
}
// allocateArray() - to iste ako allocate
void *allocateArray(size_t elementSize, size_t elementCount)
{
    if (control_overflow()) {
        structure.array[structure.index].pointer = calloc(elementCount, elementSize);
        if (structure.array[structure.index].pointer == NULL) {
            --structure.index;
            return NULL;
        }
        structure.array[structure.index].reference = 1;
        structure.array[structure.index].type = common;
        structure.array[structure.index].myfather = NULL;
        return structure.array[structure.index].pointer;
    }
    return NULL;
}
// allocateArray2D() - podla zadania + komentare vo vnutri
void **allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts)
{
    if (control_overflow()) {
        int position_father = structure.index;
        // inicializacia vonkajsieho pola == father
        structure.array[position_father].pointer = NULL;
        structure.array[position_father].myfather = NULL;
        structure.array[position_father].pointer2D = calloc(subarrays, sizeof(void *));
        if (structure.array[position_father].pointer2D == NULL) {
            --structure.index;
            return NULL;
        }
        structure.array[position_father].reference = 1;
        structure.array[position_father].type = father;
        structure.array[position_father].length = 0;

        // inicializacia vnutornych poli == child
        for (size_t i = 0; i < subarrays; i++) {
            // kontrola overflow structury
            if (control_overflow()) {
                // pripad stvorcoveho 2D pola
                if (elementCounts == NULL) {
                    structure.array[position_father].pointer2D[i] = calloc(subarrays, elementSize);
                } else {
                    structure.array[position_father].pointer2D[i] = calloc(elementCounts[i], elementSize);
                }
                if (structure.array[position_father].pointer2D[i] == NULL) {
                    // chyba pri alokovani pamate - vratim do povodneho stavu - vyuzitie postupneho pricitania ++length
                    --structure.index;
                    for (int j = 1; j <= structure.array[position_father].length; j++) {
                        free(structure.array[position_father + j].pointer);
                        --structure.index;
                        structure.array[position_father + j].pointer = NULL;
                    }
                    // free + vycistenie premennych, ktore by robili inak problem
                    free(structure.array[position_father].pointer2D);
                    --structure.index;
                    structure.array[position_father].pointer2D = NULL;
                    structure.array[position_father].type = common;
                    return NULL;
                }
                ++structure.array[position_father].length;
                structure.array[structure.index].pointer = structure.array[position_father].pointer2D[i];
                structure.array[structure.index].reference = 1;
                structure.array[structure.index].type = child;
                structure.array[structure.index].myfather = &structure.array[position_father];
                structure.array[structure.index].pointer2D = NULL;
                structure.array[structure.index].length = subarrays;
            } else {
                // nezdari sa alokacia structury - cize vsetko mazem do povodneho stavu
                for (int j = 1; j <= structure.array[position_father].length; j++) {
                    free(structure.array[position_father + j].pointer);
                    --structure.index;
                    structure.array[position_father + j].pointer = NULL;
                }
                // free + vycistenie premennych, ktore by robili inak problem
                --structure.index;
                free(structure.array[position_father].pointer2D);
                structure.array[position_father].pointer2D = NULL;
                structure.array[position_father].type = common;
                return NULL;
            }
        }
        return structure.array[position_father].pointer2D;
    }
    return NULL;
}

// acquire() - podla zadania + komentare
void acquire(void *memory)
{
    for (int i = 0; i <= structure.index; i++) {
        // ak zvysujem referenciu na vonkajsie pole v 2D poli, musim prehladavat pointer2D jednotlivych sektorov
        if (structure.array[i].type == father) {
            if (structure.array[i].pointer2D == memory) {
                ++structure.array[i].reference;
                return;
            }
        }
        if (structure.array[i].pointer == memory) {
            ++structure.array[i].reference;
            return;
        }
    }
}
// acquireArray2D() - podla zadania - postupne prechadzam prvky 2D pola a zvysujem reference
void acquireArray2D(void **array)
{
    for (int i = 0; i <= structure.index; i++) {
        if (structure.array[i].type == father) {
            if (structure.array[i].pointer2D == array) {
                ++structure.array[i].reference;
                for (int j = 1; j <= structure.array[i].length; j++) {
                    ++structure.array[j + i].reference;
                }
                return;
            }
        }
    }
}
// release() - podla zadania + komentare
bool release(void *memory)
{
    for (int i = 0; i <= structure.index; i++) {
        // ak ide o vonkajsie pole - prehladavam pointet2D
        if (structure.array[i].type == father) {
            if (structure.array[i].pointer2D == memory) {
                --structure.array[i].reference;
                if (structure.array[i].reference < 1) {
                    // v jednotlivych podpoliach mazem pointre na vonkajsie pole
                    for (int j = 1; j <= structure.array[i].length; j++) {
                        structure.array[i + j].myfather = NULL;
                        structure.array[i + j].type = common;
                    }
                    structure.array[i].pointer = NULL;
                    free(structure.array[i].pointer2D);
                    structure.array[i].pointer2D = NULL;
                    structure.array[i].type = common;
                    return true;
                }
                return false;
            }
        }
        // ak ide o podpole, pole, obycajnu pamat
        if (structure.array[i].pointer == memory) {
            --structure.array[i].reference;
            if (structure.array[i].reference < 1) {
                // ak ide o podpole
                if (structure.array[i].type == child) {
                    for (int j = 0; j < structure.array[i].length; j++) {
                        // hladam vo vonkajsom poli pointer na podpole a vymazem ho
                        if (structure.array[i].myfather->pointer2D[j] == structure.array[i].pointer) {
                            structure.array[i].myfather->pointer2D[j] = NULL;
                            break;
                        }
                    }
                }
                structure.array[i].pointer2D = NULL;
                structure.array[i].myfather = NULL;
                free(structure.array[i].pointer);
                structure.array[i].pointer = NULL;
                return true;
            }
        }
    }
    return false;
}
// releaseArray2d() - podla zadania
bool releaseArray2D(void **array)
{
    for (int i = 0; i <= structure.index; i++) {
        if (structure.array[i].type == father) {
            if (structure.array[i].pointer2D == array) {
                for (int j = 1; j <= structure.array[i].length; j++) {
                    // prechadzam pointre na podpolia, ktore este existuju
                    if (structure.array[i + j].pointer != NULL) {
                        --structure.array[i + j].reference;
                        if (structure.array[i + j].reference < 1) {
                            free(structure.array[i + j].pointer);
                            structure.array[i + j].pointer = NULL;
                        }
                    }
                }
                --structure.array[i].reference;
                if (structure.array[i].reference < 1) {
                    // pripad ak este existuju nejake podpolia - kontrolujem + mazem pointer na vonkajsie pole
                    for (int j = 1; j <= structure.array[i].length; j++) {
                        if (structure.array[i + j].pointer != NULL) {
                            structure.array[i + j].myfather = NULL;
                            structure.array[i + j].type = common;
                        }
                    }
                    free(structure.array[i].pointer2D);
                    structure.array[i].pointer2D = NULL;
                    structure.array[i].type = common;
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

