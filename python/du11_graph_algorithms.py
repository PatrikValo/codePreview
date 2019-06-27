#!/usr/bin/env python3

# Povolene knihovny: copy, math, collections
# Z knihovny collections se vam muze hodit datova struktura deque:

from collections import deque

# IB002 Domaci uloha 11.
#
# Tento tyden bude vasim ukolem implementovat dva grafove algoritmy.
# Ukoly jsou zamereny na aplikace pruchodu grafem.
#
# Reprezentace grafu je stejna jako v ukolu cv11, tedy matici sousednosti.
# Matice je indexovana od [0][0], vrcholum odpovidaji cisla 0 .. graph.size-1.
# V matici je na indexu [u][v] hodnota True, pokud graf obsahuje hranu u -> v,
# jinak je tam hodnota False.
#
# Grafy (i neorientovane!) mohou obsahovat smycky (tj. situace, kdy v matici
# na indexu [u][u] je True) a mohou byt i nesouvisle.
#
# Pripomenuti prace s frontou typu deque:
# inicializace fronty: queue = deque() nebo queue = deque([seznam prvku])
# vlozeni prvku do fronty: queue.append(prvek)
# vybrani prvku z fronty: queue.popleft(prvek)
#
# Definici tridy Graph nijak nemodifikujte, ani nepridavejte zadne atributy.
# Zamerne se v teto uloze budete muset obejit bez pomocnych poli ve tride
# Graph; budete muset pouzit lokalni promenne a pripadne parametry v rekurzi.
#
# Nepouzivejte globalni promenne. I kdyz je mozne, ze vyhodnocovaci sluzba
# neodhali vsechna pouziti globalnich promennych, u implementacnich testu
# vas pouzivani globalnich promennych zbytecne pripravi o body. Ma tedy smysl
# se naucit programovat spravne uz ted.


class Graph:
    """Trida Graph drzi graf reprezentovany matici sousednosti.
    Atributy:
        size: velikost (pocet vrcholu) grafu
        matrix: matice sousednosti
                [u][v] reprezentuje hranu u -> v
    """

    def __init__(self, size):
        self.size = size
        self.matrix = [[False] * size for _ in range(size)]


# Ukol 1.
# Implementujte funkci colourable, ktera zjisti, zda je dany neorientovany graf
# obarvitelny dvema barvami tak, aby kazde dva sousedni vrcholy mely ruznou
# barvu.
#
# Neorientovany graf v nasi reprezentaci znamena, ze
#    graph.matrix[u][v] == graph.matrix[v][u] pro vsechny vrcholy u, v.

def colourable(graph):
    """Zjisti, zda je zadany neorientovany graf obarvitelny dvema barvami.
    Vstup:
        graph - neorientovany graf typu Graph
    Vystup:
        True, pokud je graf obarvitelny dvema barvami
        False, jinak
    casova slozitost: O(n^2), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(n), kde n je pocet vrcholu grafu
    """
    if graph.size < 1:
        return True
    Queue = deque()
    Set = set(i for i in range(graph.size))
    while Set != set():
        Queue.append(Set.pop())
        number_of_parent = 1
        number_of_children = 0
        while Queue:
            pivot = Queue.popleft()
            if pivot in Set:
                Set.remove(pivot)
            for v in range(graph.size):
                if graph.matrix[pivot][v] == True:
                    if v == pivot:
                        return False
                    if v not in Queue and v in Set:
                        Queue.append(v)
                        number_of_children += 1
            number_of_parent -= 1
            if number_of_parent == 0:
                number_of_parent = number_of_children
                number_of_children = 0
                for i in Queue:
                    for j in Queue:
                        if graph.matrix[i][j] == True:
                            if i != j:
                                return False                        
    return True


# Ukol 2.
# Implementujte funkci compute_dependencies, ktera pro zadany orientovany graf
# spocita topologicke usporadani vrcholu, tj. ocislovani vrcholu takove, ze
# kazda hrana vede z vrcholu s nizsim cislem do vrcholu s vyssim cislem.
#
# Vystupem je pole zadavajici topologicke usporadani (ocislovani vrcholu),
# kde na prvni pozici (tedy s indexem 0) je vrchol nejmensi
# v tomto usporadani, tj. nevede do nej zadna hrana,
# a na posledni pozici vrchol nejvetsi, tj. nevede z nej zadna hrana.
# Pokud topologicke usporadani neexistuje, algoritmus vraci None.
#
# Priklad:
#    mejme graf s vrcholy 0, 1, 2 a hranami 0 -> 1, 2 -> 1, 2 -> 0;
#    vystupem bude pole (Pythonovsky seznam] [2, 0, 1]
def compute_n(graph, alist, u, finish):
    for number in alist:
        if graph.matrix[u][number] == True:
            return [None]
    for v in range(graph.size):
        if graph.matrix[u][v] == True:
            if v not in finish:
                alist.extend([u])
                finish = compute_n(graph, alist, v, finish)
                if finish == [None]:
                    return [None]
    finish.extend([u])    
    return finish
def compute_dependencies(graph):
    """Spocita topologicke usporadani vrcholu v grafu.
    Vstup:
        graph - orientovany graf typu Graph
    Vystup:
        pole cisel reprezentujici topologicke usporadani vrcholu
        None, pokud zadne topologicke usporadani neexistuje
    casova slozitost: O(n^2), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(n), kde n je pocet vrcholu grafu
    """
    Set = set(i for i in range(graph.size))
    finish = []
    while Set != set():
        pivot = Set.pop()
        if pivot in finish:
            continue
        finish.extend(compute_n(graph, [], pivot, []))
        if finish[-1] == None:
            return None
    if finish == [] or len(finish) == 1:
        return finish
    finish.reverse()
    return finish
def make_graph(graph, filename):
    with open(filename, 'w') as f:
        f.write("digraph MyGraph {\n")
        make_graphviz(graph, f)
        f.write("}\n")


def make_graphviz(graph, f):
    for u in range(graph.size):
        for v in range(graph.size):
            if graph.matrix[u][v]:
                f.write('"{}" -> "{}"\n'.format(u, v))


def print_matrix(graph):
    for u in range(graph.size):
        for v in range(graph.size):
            print(1 if graph.matrix[u][v] else 0, end=" ")
        print()
