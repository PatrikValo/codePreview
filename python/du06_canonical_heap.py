#!/usr/bin/env python3


# IB002 Domaci uloha 6.
#
# V nasledujicim textu pouzivame pojem "halda" ve vyznamu "binarni halda".
#
# Minimova halda je v kanonickem tvaru, pokud pro kazdy jeji prvek se dvema
# potomky plati, ze jeho levy potomek je mensi nez ten pravy nebo se oba
# rovnaji.
#
# Je v kanonickem tvaru | Neni v kanonickem tvaru
#                       |
#       (1)             |           (1)
#      /   \            |          /   \
#    (2)   (3)          |        (3)   (2)


# Trida representujici minimovou haldu. Pro praci s ni muzete s vyhodou pouzit
# funkce, ktere jste implementovali v zakladnim domacim ukolu.
import math

class MinHeap:
    def __init__(self):
        self.size = 0
        self.array = []

def parent_index(i):
    """Vrati index rodice prvku na pozici 'i'.
    Pokud neexistuje, vrati None.
    """
    if i == 0:
        return None
    return math.floor((i-1)/2)


def left_index(i):
    """Vrati index leveho potomka prvku na pozici 'i'."""
    return (2*i)+1


def right_index(i):
    """Vrati index praveho potomka prvku na pozici 'i'."""
    return (2*i)+2


def parent(heap, i):
    """Vrati rodice prvku na pozici 'i' v halde 'heap'.
    Pokud neexistuje, vrati None.
    """
    tmp = parent_index(i)
    if tmp != None:
        return heap.array[tmp]
    return None


def left(heap, i):
    """Vrati leveho potomka prvku na pozici 'i' v halde 'heap'.
    Pokud neexistuje, vrati None.
    """
    tmp = left_index(i)
    if tmp > heap.size - 1:
        return None
    return heap.array[tmp]


def right(heap, i):
    """Vrati praveho potomka prvku na pozici 'i' v halde 'heap'.
    Pokud neexistuje, vrati None.
    """
    tmp = right_index(i)
    if tmp > heap.size - 1:
        return None
    return heap.array[tmp]


def swap(heap, i, j):
    """Prohodi prvky na pozicich 'i' a 'j' v halde 'heap'."""
    heap.array[i], heap.array[j] = heap.array[j], heap.array[i]


# Ukol 1.
# Vasim prvnim ukolem je implementovat funkci is_canonical_min_heap(heap),
# ktera overi, zda je zadana halda 'heap' korektni minimovou haldou
# v kanonickem tvaru. Pokud ano, vrati True, v opacnem pripade vrati False.
#
# Prazdna nebo jednoprvkova halda je v kanonickem tvaru implicitne. Mejte na
# pameti, ze halda v kanonickem tvaru musi splnovat take pozadavky kladene na
# minimovou haldu.

def is_canonical_min_heap(heap):
    """
    vstup: 'heap' typu MinHeap
           (je zaruceno, ze heap.size je velikost pole heap.array;
            neni zaruceno, ze prvky heap.array splnuji haldovou podminku
            nebo podminku kanonickeho tvaru)
    vystup: True, pokud je 'heap' minimova halda v kanonickem tvaru
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet prvku 'heap'
    """
    i = 0
    while i <= (math.floor((heap.size - 2)/2)):
        parent_node = heap.array[i]
        left_node = left(heap, i)
        right_node = right(heap, i)
        if right_node != None:
            if left_node > right_node:
                return False
        if left_node < parent_node:
            return False
        i += 1
    return True


# Ukol 2.
# Druhym ukolem je implementovat funkci canonise_min_heap(heap), ktera zadanou
# minimovou haldu 'heap' prevede na kanonicky tvar. Funkce bude menit primo
# haldu zadanou v argumentu, proto nebude vracet zadnou navratovou hodnotu.
#
# Napoveda:
# Pro algoritmus s linearni casovou slozitosti je potreba postupovat takto:
# - Rekurzivne resime od korene k listum haldy;
# - pro kazdy uzel haldy:
#   + zkontrolujeme, jestli potomci splnuji vlastnost kanonickeho tvaru;
#     pokud ne:
#     * prohodime hodnoty leveho a praveho potomka;
#     * tim se muze pokazit vlastnost haldy v pravem podstrome, proto
#       probublame problematickou hodnotu z korene praveho podstromu
#       tak hluboko, aby uz neporusovala vlastnost haldy (pri tomto bublani
#       opravujeme pouze vlastnost haldy, kanonicky tvar neresime)
#   + mame tedy korektni minimovou haldu, ktera navic splnuje kanonicky
#     tvar od tohoto uzlu smerem nahoru;
#   + pokracujeme v rekurzi vlevo a vpravo.

def canonise_min_heap(heap):
    """
    vstup: 'heap' korektni minimova halda typu MinHeap
    vystup: funkce nic nevraci, vstupni halda 'heap' je prevedena
            do kanonickeho tvaru (pritom obsahuje stejne prvky jako na zacatku)
    casova slozitost: O(n), kde 'n' je pocet prvku 'heap'
    """
    i = 0
    while i <= (math.floor((heap.size - 2)/2)):
        parent_node = heap.array[i]
        left_node = left(heap, i)
        right_node = right(heap, i)
        if right_node != None:
            if left_node > right_node:
                l_index = left_index(i)
                r_index = right_index(i)
                swap(heap, l_index, r_index)
                parent_i = r_index
                while parent_i <= (math.floor((heap.size - 2)/2)):
                    parent_node = heap.array[parent_i]
                    left_node = left(heap, parent_i)
                    right_node = right(heap, parent_i)
                    if right_node != None:
                        if left_node > right_node and right_node < parent_node:
                            r_index = right_index(parent_i)
                            swap(heap, r_index, parent_i)
                            parent_i = r_index
                            continue
                        if right_node > parent_node and left_node > parent_node:
                            break
                    if left_node < parent_node:
                        l_index = left_index(parent_i)
                        swap(heap, l_index, parent_i)
                        parent_i = l_index
                    else:
                        break
        i += 1

#--------------------- TESTY-----------------------#
"""Control"""
# TESTY VYTVORIL A. HOFMANN
# NETESTUJE SE SLOZITOST!

DATA = [([],True),([0],True),([5,1,2],False),([1,5,2],False),([1,2,3,4],True),([1,2,3,2],True),([1,3,5,2],False),
        ([1,2,3,5,4],False),([1,2,3,4,5,7],True),([1,2,3,4,5,7,6],False),([1,2,3,4,5,6,7],True),
        ([1,1,1,3,4,1,2,6,7,8,9,10,11,5,12],True),([10,20,30,22,26,30,30,23,24,27,29,31,31,31,35],True),
        ([1,3,10,4,5,15,20,8,12,5,9,16,18,21,28,9,10,13,15,6,7,9,9,20,22,21,25,28,32,29,30],True),
        ([-1,0,-1,0,0,-1],False),([-1,0,-1,0,0,0],False)]
DATA2 = [[],[0],[1,6,2],[1,2,3,4],[1,2,3,4,5], [2, 5, 3, 8, 6, 9, 4, 10, 9, 8, 7], [1,2,1,3,4,5,1,6,7,8,9,10,11,12,1],
        [1,2,1,3,4,5,1,6,7,8,9,10,11,12,1,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27, 1],
        [1,2,1,3,4,5,1,6,7,8,9,10,11,12,1,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27, 1, 28, 29, 30, 31, 32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,1],
        [1,2,3,5,4],[1,2,3,4,5,7],[1,2,3,4,5,7,6],[1,2,3,4,5,6,7],[1,8,4,9,10,6,5],
        [1,1,1,3,4,1,2,6,7,8,9,10,11,5,12],[10,20,30,22,26,30,30,23,24,27,29,31,31,31,35],
        [1,3,10,4,5,15,20,8,12,5,9,16,18,21,28,9,10,13,15,6,7,9,9,20,22,21,25,28,32,29,30],
        [-1,0,-1,0,0,-1],[-1,0,-1,0,0,0]]
def test_end(heap):
    print("\tHalda: ", heap.array)
    print("\tHalda jako strom:");
    print_heap(heap)
    print("\nTesty ukonceny z duvodu chyby.")
    raise SystemExit(0)

def test_is_canonical_min_heap():
    for lst in DATA:
        heap = MinHeap()
        heap.array = lst[0]
        heap.size = len(lst[0])
        result = is_canonical_min_heap(heap)
        if result != lst[1]:
            print("NOK!")
            print("\tOcekavany vystup:", lst[1])
            print("\tDostano:", result)
            test_end(heap);

def test_canonise_min_heap():
    import copy
    for lst in DATA2:
        heap = MinHeap()
        heap.array = lst
        heap.size = len(lst)
        heap2 = MinHeap()
        heap2.array = copy.copy(lst)
        heap2.size = len(lst)
        canonise_min_heap(heap)
        if not is_canonical_min_heap(heap):
            print("NOK!")
            print("\tcanonise_min_heap() NEZMENILA haldu do kanonicke minimove haldy.")
            print("\tVstupni halda: ", heap2.array)
            print("\tVstupni jako strom:")
            print_heap(heap2)
            print()
            test_end(heap);

def print_heap(heap):
    import math
    max_level = int(math.log(heap.size+1,2))
    for i in range(heap.size):
        level = int(math.log(i+1,2))+1
        tab = (max_level+1-level)**2;
        formated = '{0: <2}'.format(str(heap.array[i]))
        print(" "*tab+"("+formated+")"+" "*tab, end="")
        if level < int(math.log(i+2,2))+1:
            print()

if __name__ == "__main__":
    print("Testovani is_canonical_min_heap()")
    test_is_canonical_min_heap()
    print("Testovani canonise_min_heap()");
    test_canonise_min_heap();
    print("Test uspesny!")

