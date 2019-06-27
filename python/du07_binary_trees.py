#!/usr/bin/env python3

# Povolene knihovny: copy, math
# Import jakekoli jine knihovny neprojde vyhodnocovaci sluzbou.
# To, ze jsou nejake knihovny povolene, neznamena, ze je nutne je pouzit.


# IB002 Domaci uloha 7.
#
# Souctovy strom je binarni strom, kde kazdy uzel ma nasledujici vlastnost:
# Pokud ma uzel alespon jednoho syna, potom je klic uzlu roven souctu klicu
# vsech jeho synu. Listy stromu tedy mohou obsahovat libovolne hodnoty.
# Za souctovy je povazovan i strom, ktery neobsahuje zadne uzly, a strom,
# ktery obsahuje prave jeden uzel.
#
# Muzete si samozrejme pridat vlastni pomocne funkce.
#
# Priklad:
# souctove stromy      nesouctove stromy
#   53       47            53       47
#  /  \        \          /  \     /
# 21  32       47        21  21   46
#             /  \                  \
#            1    46                 1

# Do nasledujicich definic trid nijak nezasahujte.
#
# Trida pro reprezentaci souctoveho stromu.
# root je koren stromu a je typu Node, nebo None, pokud je strom prazdny.
#
# Pro vykreslovani stromu muzete pouzit funkci make_graph z cv07.

class SumTree:
    def __init__(self):
        self.root = None


# Trida pro reprezentaci uzlu v souctovem strome.
# key je hodnota uzlu, ktera ma byt rovna souctu hodnot vsech synu.

class Node:
    def __init__(self):
        self.key = 0
        self.left = None
        self.right = None


# Ukol 1.
# Vasim prvnim ukolem je napsat funkci, ktera vybuduje uplny souctovy strom ze
# zadaneho pole. Listy stromu budou prave prvky pole v poradi zleva doprava.
# Delka pole bude vzdy mocninou dvojky.
#
# Napriklad:
# Z pole [1,2,3,4] vznikne strom:
#      10
#    /    \
#   3      7
#  / \    / \
# 1   2  3   4

index = 0 
def recursion(length, array):
    global index
    if  length == 1:
        new_node = Node()
        new_node.key = array[index]
        index += 1
        return new_node
    else:
        node = Node()
        node.left = (recursion(length//2, array))
        node.right = (recursion(length//2, array))
        node.key = node.left.key + node.right.key
        return node           
def build_sum_tree(array):
    """
    vstup: pole (Pythonovsky seznam) 'array' cisel delky 'n',
           kde 'n' je nejaka mocnina dvojky
    vystup: korektni strom typu SumTree, ktery ma v listech (v poradi zleva
            doprava) hodnoty ze zadaneho pole 'array'
            strom musi byt uplny, tj. vsechna jeho patra musi byt zcela
            zaplnena
    casova slozitost: O(n)
    """
    new_tree = SumTree()
    if array == []:
        return False
    global index
    index = 0
    new_tree.root = recursion(len(array), array)
    return new_tree
"""        

def recursion(array):
    if len(array) == 1:
        new_node = Node()
        new_node.key = array[0]
        new_node.left = None
        new_node.right = None
        return new_node
    else:
        length = len(array)//2
        node = Node()
        node.left = (recursion(array[:length]))
        node.right = (recursion(array[length:]))
        node.key = node.left.key + node.right.key
        return node    
        
def build_sum_tree(array):
    vstup: pole (Pythonovsky seznam) 'array' cisel delky 'n',
           kde 'n' je nejaka mocnina dvojky
    vystup: korektni strom typu SumTree, ktery ma v listech (v poradi zleva
            doprava) hodnoty ze zadaneho pole 'array'
            strom musi byt uplny, tj. vsechna jeho patra musi byt zcela
            zaplnena
    casova slozitost: O(n)

    new_tree = SumTree()
    if array == []:
        return False
    new_tree.root = recursion(array)
    return new_tree
"""

# Ukol 2.
# Vasim druhym ukolem je napsat funkci is_sum_tree, ktera overi, zda je strom
# souctovy. Pokud ano, vraci True, jinak False.
def is_sum_recursion(node):
    if node.left == None and node.right == None:
        return node.key
    elif node.left == None:
        if node.right.key != node.key:
            return False
        return is_sum_recursion(node.right)
    elif node.right == None:
        if node.left.key != node.key:
            return False
        return is_sum_recursion(node.left)
    else:
        tmp_left = is_sum_recursion(node.left)
        if type(tmp_left) == bool:
            return False
        tmp_right = is_sum_recursion(node.right)
        if type(tmp_right) == bool:
            return False
        if (tmp_left + tmp_right) == node.key:
            return node.key
        return False
def is_sum_tree(tree):
    """
    vstup: 'tree' typu SumTree
           (je zaruceno, ze uzly ve strome jsou typu Node;
            neni zaruceno, ze splnuji souctovou podminku)
    vystup: True, pokud je 'tree' korektni SumTree, tj. vsechny jeho uzly
                  splnuji souctovou podminku
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet prvku 'tree'
    """
    if (tree == None or tree.root == None):
        return True
    if type(is_sum_recursion(tree.root)) != bool:
        return True
    return False
build_sum_tree([1,2,3,4,5,6,7,8])
