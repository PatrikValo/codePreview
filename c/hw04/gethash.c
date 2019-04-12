#include "hash_helper.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*--------GlobalStructure--------*/
enum function
{
    x,
    c16,
    c32,
    md5
};
/* structure{}
 * pointer - ukazuje na nacitany subor
 * bytes - urcuje velkost file
 * index - hovori o tom, kolko hashov budem vytvarat / kolko hashovacich funkcii mam ulozenych v array
 * array - ukladam si sem konkretne hashovacie funkcie (repekt. premmenne, ktore ich reprezentuju) - potom ich
 * zoradim a volam v spravnom poradi
 */
struct structure
{
    unsigned char pointer[8000];
    unsigned long bytes;
    int index;
    enum function array[4];
    FILE *file;
    x_context *xor_context;
    crc16_context *c16_context;
    crc32_context *c32_context;
    MD5_CTX *md5_context;
    unsigned char MD5_result[16];
};


/*---------------Code-----------------*/
// initStructure() - vynujujem pamat do ktorej budem ukladat enum function + vynulujem index
void initStructure(struct structure *which_function)
{
    // max pocet parametrov => 4 - duplicitne volanie parametrov kontrolujem
    which_function->bytes = 0;
    which_function->index = 0;
    which_function->file = NULL;
    memset(which_function->array, 0, 4 * sizeof(enum function));
    memset(which_function->MD5_result, 0, 16 * sizeof(unsigned char));
}

// isAlreadyInArray() - kontrolujem ci som neobdrazal rovnake vstupne parametre
bool isAlreadyInArray(enum function value, struct structure *which_function)
{
    for (int i = 0; i < which_function->index; i++) {
        if (which_function->array[i] == value) {
            return true;
        }
    }
    return false;
}

// cmpfunc() - comparison function - funkcia urcena pre qsort
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// printOnScreen() - funkcia, ktora vypisuje v urcenom formate informacie o hashoch
void printOnScreen(char *name, enum function type, bool hex, struct structure *which_function)
{
    fprintf(stdout, "%s: ", name);
    switch (type) {
    case x:
        if (hex) {
            fprintf(stdout, "0x%02x\n", which_function->xor_context->result);
        } else {
            fprintf(stdout, "%u\n", which_function->xor_context->result);
        }
        break;
    case c16:
        if (hex) {
            fprintf(stdout, "0x%02x\n", which_function->c16_context->crc);
        } else {
            fprintf(stdout, "%u\n", which_function->c16_context->crc);
        }
        break;
    case c32:
        if (hex) {
            fprintf(stdout, "0x%08x\n", which_function->c32_context->crc);
        } else {
            fprintf(stdout, "%u\n", which_function->c32_context->crc);
        }
        break;
    case md5:
        for (int i = 0; i < 16; i++) {
            fprintf(stdout, "%02x", which_function->MD5_result[i]);
        }
        fprintf(stdout, "\n");
        break;
    default:
        break;
    }
    return;
}
void initHashFunctions(struct structure *which_function)
{
    for (int i = 0; i < which_function->index; i++) {
        switch (which_function->array[i]) {
        case x:
            which_function->xor_context->result = 0;
            break;
        case c16:
            crc16_init(which_function->c16_context);
            break;
        case c32:
            crc32_init(which_function->c32_context);
            break;
        case md5:
            MD5_Init(which_function->md5_context);
            break;
        default:
            break;
        }
    }
    return;
}
// xorHash - implementacia hashovacej funkcie - XOR
void xorHash(unsigned char *file, unsigned long load, bool init, x_context *xor_context)
{
    char letter;
    unsigned long index = 0;
    while (index < load) {
        letter = file[index];
        if (index == 0 && init == true) {
            index++;
            xor_context->result = letter;
            continue;
        }
        xor_context->result ^= letter;
        index++;
    }
    return;

}
// c16Hash - volam uz implementovane funkcie pre hashovaciu funkciu - C16
void c16Hash(unsigned char *file, unsigned long load, crc16_context *c16_context)
{
    char letter;
    unsigned long index = 0;
    while (index < load) {
        letter = file[index];
        crc16_update(c16_context, letter);
        index++;
    }
    return;
}
// c32Hash - volam uz implementovane funkcie pre hashovaciu funkciu - C32
void c32Hash(unsigned char *file, unsigned long load, crc32_context *c32_context)
{
    unsigned int byte;
    unsigned long index = 0;
    while (index < load) {
        byte = file[index];
        byte = reverse(byte);
        for (int j = 0; j <= 7; j++) {
            if ((int)(c32_context->crc ^ byte) < 0)
                c32_context->crc = (c32_context->crc << 1) ^ 0x04C11DB7;
            else
                c32_context->crc = c32_context->crc << 1;
            byte = byte << 1;
        }
        index++;
    }
    return;
}
// md5Hash - volam uz implementovane funkcie pre hashovaciu funkciu - MD5
void md5Hash(unsigned char *file, unsigned long load, MD5_CTX *md5_context)
{
    MD5_Update(md5_context, file, load);
    return;
}

int loadCommand(int argc, char *argv[], struct structure *which_function, bool *f, bool *hex)
{
    int i = 1;
    while (i < argc) {
        // XOR
        if (strcmp(argv[i], "-xor") == 0) {
            if (!isAlreadyInArray(x, which_function)) {
                which_function->array[which_function->index] = x;
                which_function->index++;
            }
            i++;
            continue;
        }
        // C16
        if (strcmp(argv[i], "-c16") == 0) {
            if (isAlreadyInArray(c16, which_function)) {
                i++;
                continue;
            }
            which_function->array[which_function->index] = c16;
            which_function->index++;
            i++;
            continue;
        }
        // C32
        if (strcmp(argv[i], "-c32") == 0) {
            if (isAlreadyInArray(c32, which_function)) {
                i++;
                continue;
            }
            which_function->array[which_function->index] = c32;
            which_function->index++;
            i++;
            continue;
        }
        // MD5
        if (strcmp(argv[i], "-md5") == 0) {
            if (isAlreadyInArray(md5, which_function)) {
                i++;
                continue;
            }
            which_function->array[which_function->index] = md5;
            which_function->index++;
            i++;
            continue;
        }
        // HEX
        if (strcmp(argv[i], "-hex") == 0) {
            *hex = true;
            i++;
            continue;
        }
        // FILE
        if (strcmp(argv[i], "-f") == 0) {
            if (*f != true) {
                *f = true;
                if (argv[i + 1] == NULL) {
                    fprintf(stderr, "Input Error: No Name of File\n");
                    return 1;
                }
                which_function->file = fopen(argv[i + 1], "rb");
                if (which_function->file == NULL) {
                    fprintf(stderr, "Load File Problem\n");
                    return 1;
                }
                i += 2;
                continue;
            }
            fprintf(stderr, "Multiple -f\n");
            fclose(which_function->file);
            return 1;
        }
        fprintf(stderr, "Input Error: Ivalid Parameter -> %s\n", argv[i]);
        if (*f == true) {
            fclose(which_function->file);
        }
        return 1;
        i++;
    }
    // Kontrola ci som obdrzal hashovaci parameter
    if (which_function->index == 0) {
        fprintf(stderr, "Input Error: No Parameter\n");
        if (*f == true) {
            fclose(which_function->file);
        }
        return 1;
    }
    return 0;
}
void doHash(struct structure *which_function)
{
    // number_of_bytes == pocet nacitanych bitov pomocou fread()
    unsigned long number_of_bytes = 0;
    // premenna - kvoli init XOR
    bool init = true;
    while (!feof(which_function->file)) {
        number_of_bytes = fread((void *)which_function->pointer, sizeof(char), 8000, which_function->file);
        which_function->bytes += number_of_bytes;
        for (int i = 0; i < which_function->index; i++) {
            switch (which_function->array[i]) {
            case x:
                xorHash(which_function->pointer, number_of_bytes, init, which_function->xor_context);
                break;
            case c16:
                c16Hash(which_function->pointer, number_of_bytes, which_function->c16_context);
                break;
            case c32:
                c32Hash(which_function->pointer, number_of_bytes, which_function->c32_context);
                break;
            case md5:
                md5Hash(which_function->pointer, number_of_bytes, which_function->md5_context);
                break;
            default:
                break;
            }
        }
        init = false;
    }
}
void mainPrint(struct structure *which_function, bool *hex)
{
    fprintf(stdout, "Length: %lu bytes\n", which_function->bytes);
    for (int i = 0; i < which_function->index; i++) {
        switch (which_function->array[i]) {
        case x:
            printOnScreen("XOR", x, *hex, which_function);
            break;
        case c16:
            printOnScreen("CRC-16", c16, *hex, which_function);
            break;
        case c32:
            which_function->c32_context->crc = reverse(~which_function->c32_context->crc);
            printOnScreen("CRC-32", c32, *hex, which_function);
            break;
        case md5:
            MD5_Final(which_function->MD5_result, which_function->md5_context);
            printOnScreen("MD5", md5, *hex, which_function);
            break;
        default:
            break;
        }
    }
}

/*-------------------------------------*/
/*----------- MAIN FUNCTION------------*/
/*-------------------------------------*/

int main(int argc, char *argv[])
{
    bool hex = false;
    bool f = false;
    // FILE *file som si definoval do which_function
    struct structure which_function;

    /* v tomto som mal chybu :) (predavanie adries ukazatelom v strukture);
     * nasledujucu cast kodu som presne robil vo funkcii initStructure();
     * problem bol ten, ze som si neuvedomil nasledovnu vec
     * - premmenna ...context_main - ma dosah len vramci funkcie
     * a ked som predal .._context = adresa (&...context_main) vsetko bolo ok
     * dokial sa neskoncila funkcia initStructure() - v tomto pripade
     * vsetky ...context ukazovali na neinicializovanu pamat;
     * rozmyslal som ze nasledujucu inicializaciu budem robit v initStructure(), lenze
     * zasa by som jej musel predvat 4*...context_main a to by nebolo asi pekne - preto
     * som to spravil v ramci mainu
     */
    x_context xor_context_main;
    crc16_context c16_context_main;
    crc32_context c32_context_main;
    MD5_CTX md5_context_main;
    which_function.xor_context = &xor_context_main;
    which_function.c16_context = &c16_context_main;
    which_function.c32_context = &c32_context_main;
    which_function.md5_context = &md5_context_main;

    if (argc == 1) {
        fprintf(stderr, "Input Error: No Parameter");
        return 1;
    }
    // inicializacia hlavnej struktury
    initStructure(&which_function);
    // nacitam si parametre z terminalu
    if (loadCommand(argc, argv, &which_function, &f, &hex)) {
        return 1;
    }
    if (f == false) {
        which_function.file = stdin;
    }
    // usporiadam si pole - aby som volal funkcie v zadanom poradi
    qsort(which_function.array, which_function.index, sizeof(enum function), cmpfunc);
    // inicializujem len tie funkcie, ktore budem ratat
    initHashFunctions(&which_function);
    // nacitanie suboru + vytvaranie hashov
    doHash(&which_function);
    // volam print
    mainPrint(&which_function, &hex);
    // zatvorenie suboru
    fclose(which_function.file);
    return 0;
}

