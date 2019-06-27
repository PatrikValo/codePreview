#!/usr/bin/env python3

# Povolene knihovny: copy, math
# Import jakekoli jine knihovny neprojde vyhodnocovaci sluzbou.
# To, ze jsou nejake knihovny povolene, neznamena, ze je nutne je pouzit.


# IB002 Domaci uloha 9.
#
# V teto uloze se budeme zabyvat binarnimi vyhledavacimi stromy.
#
# V prvni casti bude Vasi ulohou sestavit skoro uplny binarni vyhledavaci strom
# obsahujici zadane klice. Vstupni pole klicu bude usporadano od nejmensich po
# nejvetsi. Vas algoritmus musi mit LINEARNI casovou slozitost vzhledem k poctu
# zadanych klicu. Tento pozadavek je splnitelny diky usporadanosti pole na
# vstupu.
#
# V druhe casti bude Vasi ulohou zjistit, jestli zadany binarni vyhledavaci
# strom je skoro uplny. Pozadovana casova slozitost je linearni vuci poctu uzlu
# ve strome.
#
# Ve treti casti bude Vasi ulohou zjistit, jestli zadany binarni vyhledavaci
# strom ma vsechny listy ve stejne hloubce. Pozadovana casova slozitost je opet
# linearni vuci poctu uzlu ve strome.
#
# Skoro uplny strom ma zaplnena vsechna patra, jen posledni nemusi byt uplne
# zaplneno (a rovnez nemusi byt doleva zarovnane).
#
# Pro ilustraci, pro vstup (1,2,3,4,5,6,7,8,9,10) je korektnim vystupem
# algoritmu z prvni casti napriklad jeden z nasledujicich stromu:
#
#             ( 5 )                           ( 7 )
#            /     \                         /     \
#          (2)     (8)                  ( 4 )       ( 9 )
#         /  \     /  \                /     \      /   \
#       (1)  (3) (6)  (9)            (2)     (6)  (8)   (10)
#              \   \    \            / \     /
#              (4) (7)  (10)       (1) (3) (5)


# Do nasledujicich definic trid nijak nezasahujte.
# Pro vykreslovani stromu muzete pouzit dodanou funkci make_graph nize.

class BSTree:
    """Trida BSTree pro reprezentaci binarniho vyhledavacicho stromu.

    Atributy:
        root   koren stromu typu Node, nebo None, pokud je strom prazdny
    """

    def __init__(self):
        self.root = None


class Node:
    """Trida Node pro reprezentaci uzlu binarniho vyhledavaciho stromu.

    Atributy:
        data    hodnota daneho uzlu (zadana pri inicializaci)
        left    odkaz na leveho potomka typu Node, nebo None, pokud neexistuje
        right   odkaz na praveho potomka typu Node, nebo None, pokud neexistuje
    """

    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data


# Ukol 1.
# Implementuje funkci build_bst, ktera dostane vzestupne serazeny seznam hodnot
# a vytvori z nich skoro uplny binarni vyhledavaci strom (typu BSTree).
def build_bst_n(array, start, end):
    if start > end:
        return None
    middle = ((start + end) // 2)
    new_node = Node(array[middle])
    new_node.left = build_bst_n(array, start, middle - 1)
    new_node.right = build_bst_n(array, middle + 1 , end)
    return new_node
def build_bst(array):
    """
    vstup: 'array' vzestupne serazene pole hodnot
    vystup: strom typu BSTree, ktery je skoro uplny (viz vyse) a obsahuje
            hodnoty z pole array
    casova slozitost: O(n), kde 'n' je delka array
    extrasekvencni prostorova slozitost:
         O(1), nepocitame do ni ovsem vstupni pole ani vystupni strom
    """
    length = len(array) - 1
    tree = BSTree()
    tree.root = build_bst_n(array, 0, length)
    return tree 


# Ukol 2.
# Implementujte funkci check_almost_complete, ktera dostane binarni vyhledavaci
# strom a otestujte, zda je skoro uplny.
def check_almost_complete_n(node, depth, minimum, maximum):
    if node is None:
        if minimum is None:
            minimum = depth
        if maximum is None:
            maximum = depth
        if maximum < depth:
            maximum = depth
        if minimum > depth:
            minimum = depth
        if minimum + 1 < maximum:
            return (False, False)
        return (minimum, maximum)
    minimum_l, maximum_l = check_almost_complete_n(node.left, depth + 1, minimum, maximum)
    minimum_r, maximum_r = check_almost_complete_n(node.right, depth + 1, minimum, maximum)
    if type(minimum_l) == bool or type(minimum_r) == bool:
        return (False,False)
    minimum = min(minimum_l,minimum_r)
    maximum = max(maximum_l,maximum_r)
    if minimum + 1 < maximum:
            return (False, False)
    return (minimum, maximum) 
    
def check_almost_complete(tree):
    """
    vstup: 'tree' binarni vyhledavaci strom typu BSTree
    vystup: True, pokud je 'tree' skoro uplny
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet uzlu stromu
    extrasekvencni prostorova slozitost: O(1) (nepocitame vstup)
    """
    result, result = check_almost_complete_n(tree.root, 0, None, None)
    if type(result) == bool:
        return False
    return True

# Ukol 3.
# Implementujte funkci check_all_leaves_same_depth, ktera overi, zda jsou
# vsechny listy zadaneho binarniho vyhledavaciho stromu ve stejne hloubce.
def check_all_leaves_same_depth_n(node, depth):
    if node is None:
        return depth
    if node.left is None:
        if node.right is None:
            return depth
        right = check_all_leaves_same_depth_n(node.right, depth + 1)
        return right
    elif node.right is None:
        left = check_all_leaves_same_depth_n(node.left, depth + 1)
        return left
    else:
        left = check_all_leaves_same_depth_n(node.left, depth + 1)
        if left == None:
            return None
        right = check_all_leaves_same_depth_n(node.right, depth + 1)
        if right == None:
            return None
    if left == right:
        return left
    return None
def check_all_leaves_same_depth(tree):
    """
    vstup: 'tree' binarni vyhledavaci strom typu BSTree
    vystup: True, pokud jsou vsechny listy 'tree' ve stejne hloubce
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet uzlu stromu
    extrasekvencni prostorova slozitost: O(1) (nepocitame vstup)
    """
    if check_all_leaves_same_depth_n(tree.root, 0) == None:
        return False
    return True

# Pomocna funkce make_graph vygeneruje .dot soubor na zaklade stromu predaneho
# v argumentu. Cilem funkce je jen zobrazit aktualni stav daneho uzlu a jeho
# potomku, nijak nekontroluje jestli se jedna o BVS.
#
# Na vygenerovany soubor si bud najdete nastroj, nebo pouzijte odkazy:
# http://sandbox.kidstrythisathome.com/erdos/ nebo http://www.webgraphviz.com/
#
# Staci zkopirovat obsah souboru do formulare webove stranky.

def make_graph(tree, filename="bst.dot"):
    def dot_node(fd, node):
        if node is None:
            return

        fd.write('{} [label="{}"]\n'.format(id(node), node.data))

        for child, lr in (node.left, 'L'), (node.right, 'R'):
            dot_node(fd, child)
            dot_node_relations(fd, node, child, lr)

    def dot_node_relations(fd, parent, node, direction):
        if node is None:
            nil = direction + str(id(parent))
            fd.write('{} [label="",color=white]\n{} -> {}\n'
                     .format(nil, id(parent), nil))
        else:
            fd.write('{} -> {}\n'.format(id(parent), id(node)))

    with open(filename, "w") as fd:
        fd.write("digraph {\n")
        fd.write("node [color=lightblue2,style=filled]\n")
        dot_node(fd, tree.root)
        fd.write("}\n")





