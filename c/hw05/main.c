#include "common.h"
int cstring_cmp(const void *a, const void *b)
{
    char **a_str = (char **)a;
    char **b_str = (char **)b;
    char *a_tmp = *a_str;
    char *b_tmp = *b_str;
    if (*a_str[0] == '.' && (strcmp(*a_str, ".") != 0 || strcmp(*a_str, "..") != 0)) {
        a_tmp = &a_str[0][1];
    }
    if (*b_str[0] == '.' && (strcmp(*b_str, ".") != 0 || strcmp(*b_str, "..") != 0)) {
        b_tmp = &b_str[0][1];
    }
    int compare;
    if ((compare = strcmp(a_tmp, b_tmp)) == 0) {
        if ((compare = strcmp(*a_str, *b_str)) > 0) {
            return -1;
        }
        return 2;
    }
    return compare;
}

int loadCurrentDir(struct main_structure *structure)
{
    size_t size;
    char *filename;
    size = pathconf(".", _PC_PATH_MAX);
    if ((filename = malloc(size)) != NULL) {
        if ((filename = getcwd(filename, size)) == NULL) {
            perror("Error: ");
            free(filename);
            return 0;
        }
        if ((structure->current_dir = opendir(filename)) == NULL) {
            perror("Error: ");
            free(filename);
            return 0;
        }
        free(filename);
        return 1;
    }
    fprintf(stderr, "Heap Error");
    return 0;
}
int loadAllDirName(struct main_structure *structure)
{
    // inicializujem si pole stringov
    if (!initCharArray(&structure->name, structure->constant)) {
        return 0;
    }

    struct dirent *open_dir;
    while ((open_dir = readdir(structure->current_dir)) != NULL) {
        // structure->hide == ls prave vtedy ak --> ./ls
        if (structure->hide == ls) {
            if (open_dir->d_name[0] == '.') {
                continue;
            }
        }
        // structure->hide == A prave vtedy ak --> ./ls -A
        if (structure->hide == A) {
            if (strcmp(open_dir->d_name, ".") == 0) {
                continue;
            }
            if (strcmp(open_dir->d_name, "..") == 0) {
                continue;
            }
        }
        // structure.hide == a prave vtedy ak --> .ls -a
        if (!appendChar(&structure->name, structure->constant, open_dir->d_name)) {
            free(structure->name.array);
            return 0;
        }
    }
    // zoradim si postupne mena podla abecedy + podla zadania
    qsort(structure->name.array, structure->name.index, sizeof(char *), cstring_cmp);
    return 1;
}
/*
 * size_t value - premenna do ktorej si ukladam cislo ktore chcem vkladat do konkretneho pola
 * char *put_string - sem si ukladam string ktory chcem ukladat do konkretneho pola
 * konkretne pole vyberam pomocou funkcii returnCharArray() a returnIntArray()
 */
int loadInformationAboutDir(struct main_structure *structure)
{
    struct stat sb;
    int error = 0;
    struct passwd *user_info;
    struct group *group_info;
    size_t value = 0;
    char *put_string = NULL;
    for (size_t i = 0; i < structure->name.index; i++) {
        if ((error = stat(structure->name.array[i], &sb)) < 0) {
            perror("Error: ");
            freeWorkPlace(structure, structure->index_of_columns - 1);
            return 0;
        }
        char mode_string[11];
        char buffer[20];
        struct tm *tmpinfo;
        for (size_t j = 0; j < structure->index_of_columns; j++) {
            switch (structure->columns[j]) {
            case mode:
                mode_to_string(sb.st_mode, mode_string);
                put_string = mode_string;
                break;
            case hard:
                value = (size_t)sb.st_nlink;
                break;
            case user_name:
                if ((user_info = getpwuid(sb.st_uid)) == NULL) {
                    perror("Error: ");
                    char str[21];
                    sprintf(str, "%u", (int)sb.st_uid);
                    put_string = str;
                    break;
                }
                put_string = user_info->pw_name;
                break;
            case group_name:
                if ((group_info = getgrgid(sb.st_gid)) == NULL) {
                    perror("Error: ");
                    char str[21];
                    sprintf(str, "%u", (int)sb.st_gid);
                    put_string = str;
                    break;
                }
                put_string = group_info->gr_name;
                break;
            case size:
                value = (size_t)sb.st_size;
                break;
            case mod_time:
                tmpinfo = localtime(&sb.st_mtime);
                strftime(buffer, 80, "%b %e %Y %R", tmpinfo);
                put_string = buffer;
                break;
            case inode:
                value = (size_t)sb.st_ino;
                break;
            default:
                break;
            }
            // nazov suboru preskakujem lebo ten mam uz nacitany
            if (structure->columns[j] == name) {
                continue;
            }
            // plnim polia, ktore maju ciselne hodnoty - hodnotou value - ktoru si pre konkretny typ pola urcujem hore
            if (structure->columns[j] == hard || structure->columns[j] == size || structure->columns[j] == inode) {
                struct int_segment* segment = returnIntArray(structure, structure->columns[j]);
                if (!appendInt(segment, structure->constant, value)) {
                    segment->index = 0;
                    freeWorkPlace(structure, structure->index_of_columns - 1);
                    return 0;
                }
            } else {
                // plnim polia stringami - put_string
                struct char_segment* segment = returnCharArray(structure, structure->columns[j]);
                if (!appendChar(segment, structure->constant, put_string)) {
                    segment->index = 0;
                    freeWorkPlace(structure, structure->index_of_columns - 1);
                    return 0;
                }
            }
        }
    }
    return 1;
}
// vyuzivam funkcie - returnIntArray() a returnCharArray() - ktore mi vratia ziadane pole
void printOutput(struct main_structure *structure)
{
    int init = 1;
    for (size_t i = 0; i < structure->name.index; i++) {
        init = 1;
        for (size_t j = 0; j < structure->index_of_columns; j++) {
            if (!init) {
                printf(" ");
            } else {
                init = 0;
            }
            if ((structure->columns[j] == hard) || (structure->columns[j] == size) || (structure->columns[j] == inode)) {
                struct int_segment* segment = returnIntArray(structure, structure->columns[j]);
                printf("%*lu", segment->len, segment->array[i]);
            } else {
                struct char_segment* segment = returnCharArray(structure,structure->columns[j]);
                if (j + 1 == structure->index_of_columns) {
                    printf("%s", segment->array[i]);
                } else {
                    printf("%-*s", segment->len, segment->array[i]);
                }
            }
        }
        printf("\n");
    }
}
void caseShow(struct main_structure *structure, char *show_parameter)
{
    for (size_t j = 7; j < strlen(show_parameter); j++) {
        switch (show_parameter[j]) {
        case 'R':
            structure->columns[structure->index_of_columns] = mode;
            structure->index_of_columns++;
            break;
        case 'L':
            structure->columns[structure->index_of_columns] = hard;
            structure->index_of_columns++;
            break;
        case 'U':
            structure->columns[structure->index_of_columns] = user_name;
            structure->index_of_columns++;
            break;
        case 'G':
            structure->columns[structure->index_of_columns] = group_name;
            structure->index_of_columns++;
            break;
        case 'S':
            structure->columns[structure->index_of_columns] = size;
            structure->index_of_columns++;
            break;
        case 'M':
            structure->columns[structure->index_of_columns] = mod_time;
            structure->index_of_columns++;
            break;
        case 'N':
            structure->columns[structure->index_of_columns] = name;
            structure->index_of_columns++;
            break;
        case 'I':
            structure->columns[structure->index_of_columns] = inode;
            structure->index_of_columns++;
            break;
        default:
            break;
        }
    }
}
int loadInput(int argc, char *argv[], struct main_structure *structure)
{
    structure->index_of_columns = 0;
    // ak nedostanem parameter volam tuto funkciu s novymi parametrami
    if (argc == 1) {
        char *tmp[3] = { "./ls", "./ls", "--show=RLUGSMN" };
        loadInput(3, tmp, structure);
        return 1;
    }
    // ak som obdrzal len jeden parameter - obdobne ako pri ziadnom parametri
    if (argc == 2) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-A") == 0) {
                structure->hide = A;
                char *tmp[3] = { "./ls", "./ls", "--show=RLUGSMN" };
                loadInput(3, tmp, structure);
                return 1;
            }
            if (strcmp(argv[i], "-a") == 0) {
                structure->hide = a;
                char *tmp[3] = { "./ls", "./ls", "--show=RLUGSMN" };
                loadInput(3, tmp, structure);
                return 1;
            }
            if (strncmp(argv[i], "--show=", 7) == 0) {
                // pokracujem dalej k implementacii nacitania --show=
                break;
            }
            // ak uzivatel zadal neplatny parameter
            char *tmp[3] = { "./ls", "./ls", "--show=RLUGSMN" };
            loadInput(3, tmp, structure);
            return 1;
        }
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-A") == 0) {
            structure->hide = A;
            continue;
        }
        if (strcmp(argv[i], "-a") == 0) {
            structure->hide = a;
            continue;
        }
        if (strncmp(argv[i], "--show=", 7) == 0) {
            char *show_parameter = argv[i];
            caseShow(structure, show_parameter);
            continue;
        }
    }
    return 1;
}
/*
 * Poziadavky som upravil - hide je enum
 *                        - spominane funkcie som dal do suboru common
 *                        - na tie switche som si vytvoril dve funkcie returnCharArray() a returnIntArray()
 * ktore vracaju ukazatel na jednotlive polia, snad je to lepsie
 *                        - snazil som sa upravit aj funkciu loadInformationAboutDir() - spolocne veci som
 * spojil do jedneho, ale casom som sa nevyhol - vnich si urcujem co sa ma dat do pomocnej premennej value alebo put_string,
 * ktore potom vkladam do pola
 *                        - pre pripad --show= som vytvoril novu funkciu
 * Snad som na nic nezabudol a je to takto lepsie
 */
int main(int argc, char *argv[])
{
    struct main_structure structure;
    structure.constant = 5;
    structure.hide = ls;
    // nacitanie z terminalu
    loadInput(argc, argv, &structure);
    // otvorim si aktualny adresar
    if (!loadCurrentDir(&structure)) {
        return 1;
    }
    // nacitam si vsetky podadresare - podla poziadavky z terminalu
    if (!loadAllDirName(&structure)) {
        closedir(structure.current_dir);
        return 1;
    }
    // inicializujem si priestor pre jednotlive polia
    if (!initWorkPlace(&structure)) {
        freeCharArray(&structure.name);
        closedir(structure.current_dir);
        fprintf(stderr, "Heap Error");
        return 1;
    }
    // nacitam info
    if (!loadInformationAboutDir(&structure)) {
        freeCharArray(&structure.name);
        closedir(structure.current_dir);
        return 1;
    }
    // vypis
    printOutput(&structure);
    // mazanie naalokovanej pamate
    freeWorkPlace(&structure, structure.index_of_columns - 1);
    freeCharArray(&structure.name);
    closedir(structure.current_dir);
    return 0;
}
