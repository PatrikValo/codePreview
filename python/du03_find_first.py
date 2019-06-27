#!/usr/bin/env python3


# IB002 Domaci uloha 3.
#
# Vasi ulohou bude s vyuzitim principu binarniho vyhledavani implementovat
# dve funkce, find_first_occurrence a find_first_greater. V obou pripadech
# musi casova slozitost vaseho algoritmu byt nejhure logaritmicka, tedy byt
# v O(log n). (Pozor, iterovani v poli ma linearni slozitost.)
# Funkce nesmi modifikovat vstupni pole.
#
# Ukol 1.
# Implementujte funkci find_first_occurrence, ktera vrati index prvniho
# vyskytu prvku key v serazenem poli numbers. Pokud se prvek v poli
# nevyskytuje, vrati -1.
#
# Priklady vstupu a vystupu:
# find_first_occurrence(2, [1, 2, 2, 2, 4]) -->  1
# find_first_occurrence(3, [1, 2, 4, 5])    --> -1

def find_first_occurrence(key, numbers):
    """
    vstup: 'key' hodnota hledaneho cisla, 'numbers' serazene pole cisel
    vystup: index prvniho vyskytu hodnoty 'key' v poli 'numbers',
            -1, pokud se tam tato hodnota nevyskytuje
    casova slozitost: O(log n), kde 'n' je pocet prvku pole 'numbers'
    """
    low = 0
    high = len(numbers)-1
    index = None
    while low <= high:
        middle = (low + high)//2
        if numbers[middle] == key:
            index = middle
            high = middle - 1
        elif numbers[middle] < key:
            low = middle + 1
        else:
            high = middle -1
    if index == None:
        return -1
    else:
        return index

# Ukol 2.
# Implementujte funkci find_first_greater modifikaci predchozi funkce
# find_first_occurrence tak, ze find_first_greater vrati index prvniho prvku
# v poli vetsiho nez key. Neni-li v poli zadny takovy, vrati -1.
#
# Priklady vstupu a vystupu:
# find_first_greater(2, [1, 2, 4, 5]) -->  2
# find_first_greater(3, [1, 2, 4, 5]) -->  2
# find_first_greater(3, [1, 2, 3])    --> -1

def find_first_greater(key, numbers):
    """
    vstup: 'key' hodnota hledaneho cisla, 'numbers' serazene pole cisel
    vystup: index prvniho vyskytu prvku vetsiho nez hodnota 'key',
            -1, pokud tam zadny takovy prvek neni
    casova slozitost: O(log n), kde 'n' je pocet prvku pole 'numbers'
    """
    low = 0
    high = len(numbers)-1
    index = None
    while low <= high:
        middle = (low + high)//2
        if numbers[middle] <= key:
            low = middle + 1
        else:
            index = middle
            high = middle -1
    if index == None:
        return -1
    else:
        return index

