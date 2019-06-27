#!/usr/bin/python3


# Zadani:
# V tomto prikladu budeme pracovat se zelenomodrymi stromy (GBTree).
# Zelenomodre stromy jsou definovany takto:
# - Zelenomodry strom je binarni vyhledavaci strom (BVS).
# - Zelenomodry strom ma vrcholy obarvene modrou nebo zelenou barvou.
# - Koren zelenomodreho stromu je zeleny.
# - Zelonomodry strom ma specialni celociselny atribut 'g_dist'.
# - Na kazde ceste z korene do listu je presne kazdy 'g_dist' uzel zeleny,
#       tj. pro g_dist = 3 je napr: zeleny (koren), modry, modry, zeleny,
#       modry, modry, zeleny, modry.
# - Prazdny strom je korektni zelenomodry strom.


class GBTree:
    """ Trida pro reprezentaci GBTree

    Atributy:
        root    koren stromu typu GBNode nebo None, pokud je strom prazdny
        g_dist  urcuje vzdalenost dvou zelenych uzlu na kazde ceste z korene
    """

    def __init__(self):
        self.root = None
        self.g_dist = None


# Nastaveni pro pouziti barev, jak jste zvykli z cv pro cerveno-cerne stromy.
# Barva se nastavuje node.color = Colors.green nebo node.color = Colors.blue.
def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    return type('Enum', (), enums)


Colors = enum('green', 'blue')


class GBNode:
    """ Struktura pro reprezentaci uzlu stromu GBTree.

    Atributy:
        key    klic uzlu
        color  barva uzlu, muze mit hodnotu Colors.green, nebo Colors.blue
        left   levy syn - atribut typu GBNode pokud syn existuje, jinak None
        right  pravy syn - atribut typu GBNode pokud syn existuje, jinak None
    """

    def __init__(self):
        self.key = 0
        self.color = Colors.green  # barva
        self.left = None  # levy potomek
        self.right = None  # pravy potomek
        self.green_children = []  # seznam zelenych potomku, jen pro ukol 3


# Ukol 1. (10 bodu)
# Implementujte funkci is_correct_GB_tree(tree), ktera overi, zda je zadany
# binarni vyhledavaci strom 'tree' korektne obarveny zelenomodry strom.
# Tj. nemusite kontrolovat vyhledavaci vlastnost, pouze obarveni uzlu.
def is_correct_n(node, depth, const):
    if node == None:
        return True
    if depth % const == 0:
        if node.color != Colors.green:
            return False
    else:
        if node.color == Colors.green:
            return False
    if is_correct_n(node.left, depth + 1, const) == False:
        return False
    if is_correct_n(node.right, depth + 1, const) == False:
        return False
    return True
def is_correct_GB_tree(tree):
    """
    vstup: 'tree' korektni BVS strom typu GBTree, ktery se ma zkontrolovat
    vystup: True pokud je 'tree' korektni zelenomodry strom, False jinak
    casova slozitost:  O(n), kde 'n' je pocet uzlu stromu 'tree'
    """
    if tree != None:
        return is_correct_n(tree.root, 0, tree.g_dist)    
    return True

# Ukol 2. (10 bodu)
# Implementujte funkci insert_to_GB_tree(tree, key), ktera prida uzel do
# korektniho zelenomodreho stromu se zadanou hodnotou klice. Do stromu se novy
# uzel vklada pouze v pripade, ze se uzel se zadanym klicem ve strome dosud
# nevyskytoval. Uzel je nutne obarvit a vlozit na spravne misto ve strome tak,
# aby i vysledny strom splnoval vlastnosti zelenomodreho stromu (obarveni i
# vyhledavaci vlastnost).
def insert_n(node, key, depth, const):
    if node == None:
        node = GBNode()
        node.key = key
        if depth % const == 0:
            node.color = Colors.green
            return node
        node.color = Colors.blue
        return node
    if node.key == key:
        return node
    if key < node.key:
        node.left = insert_n(node.left, key, depth + 1, const)
        return node
    node.right = insert_n(node.right, key, depth + 1, const)
    return node
def insert_to_GB_tree(tree, key):
    """
    vstup: 'tree' korektni zelenomodry strom, do ktereho se ma vlozit novy uzel
            'key' hodnota, ktera se ma vlozit do stromu 'tree'
    vystup: nic, upravujeme primo vstupni strom
    casova slozitost: O(h), kde 'h' je delka nejdelsi vetve od korene k listu
    """
    tree.root = insert_n(tree.root, key, 0, tree.g_dist)

# Ukol 3. (15 bodu)
# Implementujte funkci set_green_children(tree), ktera v zadanem korektnim
# zelenomodrem strome 'tree' nastavi v kazdem zelenem uzlu pole
# 'green_children'. V tomto poli budou v poradi zleva doprava vlozeny odkazy
# na vsechny nejblizsi zelene potomky zadaneho uzlu (tj. prave ti, kteri jsou
# ve vzdalenosti 'g_dist'). V modrych uzlech bude pole prazdne.
#
# Napr. pro strom nize bude v uzlu s klicem 10 nastaveno pole s odkazy na uzly
# s klici 6, 8 a 12, v uzlu s klicem 6 bude pole s odkazem na jediny uzel, ten
# s klicem 5. Vsechna ostatni pole budou prazdna. Slozenymi zavorkami jsou
# oznaceny zelene uzly, tzn. 'g_dist' je 2.
#          {10}
#        /      \
#      (7)      (23)
#     /   \     /
#   {6}   {8} {12}
#  /
# (4)
#   \
#   {5}
def set_green_n(node, depth, const, alist):
    if node == None:
        return alist
    if depth / const == 1:
        depth = 0
        alist.append(node)
        node.green_children = set_green_n(node.left, depth + 1, const, node.green_children)
        node.green_children = set_green_n(node.right, depth + 1, const, node.green_children)
        return alist
    alist = set_green_n(node.left, depth + 1, const, alist)
    alist = set_green_n(node.right, depth + 1, const, alist)
    return alist
def set_green_children(tree):
    """
    vstup: 'tree' korektni zelenomodry strom
    vystup: nic, upravujeme primo vstupni strom
    casova slozitost: O(n), kde 'n' je pocet uzlu stromu 'tree'
    """
    if tree != None:
        if tree.root != None:
            tree.root.green_children = set_green_n(tree.root, 0, tree.g_dist, tree.root.green_children)

# Ukol 4. (15 bodu)
# Implementujte funkci join_two_GB_trees(minus_tree, plus_tree), ktera umi
# spojit dva zadane GBTree, pricemz predpokladejte, ze 'minus_tree' obsahuje
# pouze zaporne klice a 'plus_tree' obsahuje jen kladne klice. Vysledny strom
# ma mit 'g_dist' rovnu 'g_dist' stromu 'plus_tree' a musi splnovat vsechny
# vlastnosti zelenomodreho stromu.
#
# POZNAMKA: Lze libovolne modifikovat vstupni stromy (neni nutne vytvaret
# kopii stromu). Napriklad muzete jeden ze stromu "zavesit" do druheho.
# Pozorne si proctete pozadavek na casovou slozitost.
def join_n(key, node, depth, const):
    if node == None:
        node = GBNode()
        node.key = key 
        if depth % const == 0:
            node.color = Colors.green
        else:
            node.color = Colors.blue
        return node
    if key < node.key:
        node.left = join_n(key, node.left, depth + 1, const)
        return node
    if key > node.key:
        node.right = join_n(key, node.right, depth + 1, const)
        return node
    return node
def join_main(minus_node, plus_tree):
    if minus_node == None:
        return plus_tree.root
    plus_tree.root = join_n(minus_node.key, plus_tree.root, 0, plus_tree.g_dist)
    plus_tree.root = join_main(minus_node.left, plus_tree)
    plus_tree.root = join_main(minus_node.right, plus_tree)
    return plus_tree.root
def join_two_GB_trees(minus_tree, plus_tree):
    """
    vstup: 'minus_tree' korektni zelenomodry strom, se zapornymi klici
           'plus_tree'  korektni zelenomodry strom, s kladnymi klici
    vystup: korektni zelenomodry strom, jehoz g_dist je rovna g_dist stromu
            'plus_tree', a ktery obsahuje prave vsechny uzly obou vstupnich
            stromu
    casova slozitost: O(n1 + h2), kde 'n1' je pocet vrcholu stromu
            'minus_tree' a 'h2' je delka nejdelsi cesty stromu 'plus_tree'
    """
    
    plus_tree.root = join_main(minus_tree.root, plus_tree)
    return plus_tree
    

"""
Soubory .dot z testu vykreslite napr. na http://www.webgraphviz.com/.
"""


########################################################################
#               Nasleduje kod testu, NEMODIFIKUJTE JEJ                 #
########################################################################


def make_graph(tree, fileName):
    """
    Zde mate k dispozici funkci `make_graph`, ktera vam z `tree` na vstupu
    vygeneruje do souboru `fileName` reprezentaci stromu pro graphviz.
    Graphviz je nastroj, ktery vam umozni vizualizaci datovych struktur,
    coz se hodi predevsim pro ladeni.
    Pro zobrazeni graphvizu muzete vyuzit:
    http://www.webgraphviz.com/
    """

    def make_node(id, label, color):
        f.write("{} [label=\"{}\", color =\"{}\"]\n".format(id, label, color))

    def make_edge(n1, n2):
        f.write("{} -> {}\n".format(n1, n2))

    def check_child(node, child, label):
        if child is None:
            make_node("{}{}".format(label, id(node)), "Nil", "white")
            make_edge(id(node), "{}{}".format(label, id(node)))
        else:
            make_edge(id(node), id(child))
            make_graphviz(child, f)

    def make_graphviz(node, f):
        if node is None:
            return
        color = "green" if node.color == 0 else "lightblue"
        make_node(id(node), node.key, color)
        check_child(node, node.left, 'L')
        check_child(node, node.right, 'R')

    with open(fileName, 'w') as f:
        f.write("digraph Tree {\n")
        f.write("node [color=lightblue2, style=filled, ordering=\"out\"];\n")
        if tree is not None:
            f.write("graph [label = \"g_dist = %i\"]\n" % tree.g_dist)
            if tree.root is not None:
                f.write("node [color=lightblue2, style=filled];\n")
                make_graphviz(tree.root, f)
        f.write("}\n")


def ib002_create_GB_node(data):
    node = GBNode()
    node.key = data[0]
    node.color = data[1]

    return node


def ib002_make_GB_nodes(list):
    if list is None or len(list) == 0:
        return None

    node = ib002_create_GB_node(list[0])
    if len(list) > 1:
        node.left = ib002_make_GB_nodes(list[1])
        node.right = ib002_make_GB_nodes(list[2])
    else:
        node.left = None
        node.right = None

    return node


def ib002_make_GB_tree(nodeList):
    tree = GBTree()
    tree.g_dist = nodeList[0]
    tree.root = ib002_make_GB_nodes(nodeList[1])

    return tree


def ib002_comp_trees(t1, t2):
    if t1 is None and t2 is None:
        return True
    if t1 is None or t2 is None:
        return False
    return t1.key == t2.key and t1.color == t2.color and \
        ib002_comp_trees(t1.left, t2.left) and \
        ib002_comp_trees(t1.right, t2.right)


ib002_trees_correct = [
    [2, []],
    [3, [(5, 1)]],
    [3, [(5, 0)]],
    [3, [(5, 0), [(3, 1), [(1, 1)], [(4, 1)]], [(7, 1)]]],
    [3, [(5, 0), [(3, 1), [(1, 1)], [(4, 1)]], [(7, 1), [(6, 1)], [(8, 1)]]]],
    [2, [(5, 0), [(3, 1), [(1, 0)], [(4, 0)]], [(7, 1), [(6, 0)], [(8, 0)]]]],
    [3, [(10, 0),
         [(5, 1), [(2, 1), [(1, 1)], [(3, 1)]], [(7, 1), [(6, 1)], [(9, 1)]]],
         [(15, 1), [(13, 1), [(12, 1)], [(14, 1)]],
          [(18, 1), [(17, 1)], [(19, 1)]]]]],
    [3, [(10, 0),
         [(5, 1), [(2, 1), [(1, 0)], [(3, 0)]], [(7, 1), [(6, 0)], [(9, 0)]]],
         [(15, 1), [(13, 1), [(12, 0)], [(14, 0)]],
          [(18, 1), [(17, 0)], [(19, 0)]]]]],
    [3, [(10, 1),
         [(5, 1), [(2, 1), [(1, 0)], [(3, 0)]], [(7, 1), [(6, 0)], [(9, 0)]]],
         [(15, 1), [(13, 1), [(12, 0)], [(14, 0)]],
          [(18, 1), [(17, 0)], [(19, 0)]]]]],
    [1, [(10, 0),
         [(5, 0), [(2, 0), [(1, 0)], [(3, 0)]], [(7, 0), [(6, 0)], [(9, 0)]]],
         [(15, 0), [(13, 0), [(12, 0)], [(14, 0)]],
          [(18, 0), [(17, 0)], [(19, 0)]]]]],
    [1, [(10, 0),
         [(5, 0), [(2, 0), [(1, 1)], [(3, 0)]], [(7, 0), [(6, 0)], [(9, 0)]]],
         [(15, 0), [(13, 0), [(12, 0)], [(14, 0)]],
          [(18, 0), [(17, 0)], [(19, 0)]]]]],
    [3, [(15, 0), [(1, 1), [],
                   [(8, 1), [(3, 0), [], [(5, 1), [(4, 1)], [(6, 1)]]],
                    [(10, 0)]]], []]],
    [3, [(15, 0), [(1, 1), [],
                   [(8, 1), [(3, 0), [], [(5, 1), [(4, 0)], [(6, 0)]]],
                    [(10, 0)]]], []]]
]


def ib002_test_is_correct_GB_tree():
    failure = False
    print("*** Testovani funkce is_correct_GB_tree: ")
    results = [True, False, True, True, True, True, False, True, False, True,
               False, True, False]

    for i in range(len(ib002_trees_correct)):
        tree = ib002_make_GB_tree(ib002_trees_correct[i])

        if is_correct_GB_tree(tree) != results[i]:
            make_graph(tree, "is_correct.dot")
            print("NOK ***\n")
            if results[i]:
                print("\tStrom je korektni zelenomodry strom, ale funkce "
                      "jej oznacila za nekorektni.\n\tStrom byl ulozen do "
                      "souboru is_correct.dot .")
            else:
                print("\tTestovany strom neni korektni zelenomodry strom, ale"
                      " funkce jej oznacila za korektni.\n\tStrom byl ulozen"
                      " do souboru is_correct.dot .")
            failure = True
            break

    if not failure:
        print("OK ***")


ib002_trees_insert = [
    [2, []],
    [2, [(7, 0)]],
    [2, [(7, 0), [(5, 1)], []]],
    [2, [(7, 0), [(5, 1)], [(9, 1)]]],
    [2, [(7, 0), [(5, 1)], [(9, 1)]]],
    [2, [(7, 0), [(5, 1), [(3, 0)], []], [(9, 1)]]],
    [2, [(7, 0), [(5, 1), [(3, 0), [(1, 1)], []], []], [(9, 1)]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], []], []], [(9, 1)]]],
    [2, [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], []],
         [(9, 1)]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1)]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1)]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1)]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1), [(8, 0)], []]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1), [(8, 0)], []]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1), [(8, 0)], [(10, 0)]]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1), [(8, 0)], [(10, 0), [], [(11, 1)]]]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1), [(8, 0)], [(10, 0), [], [(11, 1), [], [(12, 0)]]]]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1), [(8, 0)],
       [(10, 0), [], [(11, 1), [], [(12, 0), [], [(13, 1)]]]]]]],
    [2,
     [(7, 0), [(5, 1), [(3, 0), [(1, 1), [], [(2, 0)]], [(4, 1)]], [(6, 0)]],
      [(9, 1), [(8, 0)], [(10, 0), [], [(11, 1), [], [(12, 0), [],
                                                      [(13, 1), [],
                                                       [(14, 0)]]]]]]]]
]


def ib002_test_insert_to_GB_tree():
    failure = False
    print("\n*** Testovani funkce insert_to_GB_tree: ")
    tree = GBTree()
    tree.g_dist = 2
    insert_list = [7, 5, 9, 9, 3, 1, 2, 4, 6, 7, 1, 8, 9, 10, 11, 12, 13, 14]

    for i in range(len(insert_list)):
        insert_to_GB_tree(tree, insert_list[i])
        tree_check = ib002_make_GB_tree(ib002_trees_insert[i + 1])

        if tree is None:
            print("NOK ***\n")
            print("\tVase implementace vraci None misto promenne typu GBTree.")
            failure = True
            break
        if not ib002_comp_trees(tree.root, tree_check.root):
            print("NOK ***\n")
            if i == 0:
                print("\tVkladalo se do prazdneho stromu")
            tree_check_before = ib002_make_GB_tree(ib002_trees_insert[i])
            make_graph(tree_check_before, "insert_before.dot")
            make_graph(tree_check, "insert_correct.dot")
            make_graph(tree, "insert_yours.dot")
            print("\tPo vlozeni klice %i nebyl vytvoren ocekavany zelenomodry"
                  " strom.\n\tStrom, do ktereho se vkladalo je v souboru "
                  "insert_before.dot . \n\tStrom, ktery vytvorila vase funkce "
                  "je v souboru insert_yours.dot .\n\tKorektni strom, ktery "
                  "mel vzniknout je v souboru insert_correct.dot ." %
                  insert_list[i])
            failure = True
            break

    if not failure:
        print("OK ***")


ib002_trees_children = [
    [2, []],
    [2, [(7, 0)]],
    [2, [(7, 0), [(5, 1)], []]],
    [2, [(7, 0), [(5, 1)], [(9, 1)]]],
    [1, [(7, 0), [(5, 0)], []]],
    [1, [(7, 0), [(5, 0)], [(9, 0)]]],
    [1, [(7, 0), [(5, 0), [(4, 0)], [(6, 0)]], [(9, 0), [(8, 0)], [(10, 0)]]]],
    [1,
     [(6, 0), [(5, 0), [(4, 0), [(3, 0), [(2, 0), [(1, 0)], []], []], []], []],
      []]],
    [2,
     [(6, 0), [(5, 1), [(4, 0), [(3, 1), [(2, 0), [(1, 1)], []], []], []], []],
      []]],
    [2,
     [(20, 0), [(5, 1), [(4, 0), [(3, 1), [(2, 0), [(1, 1)], []], []], []],
                [(12, 0), [(11, 1)], []]],
      [(26, 1), [(22, 0)], []]]],
    [1, [(1, 0), [], [(2, 0), [], [(3, 0), [], [(10, 0), [(9, 0), [(8, 0),
                                                                   [(7, 0),
                                                                    [(6, 0)],
                                                                    []], []],
                                                          []], []]]]]],
    [2, [(1, 0), [], [(2, 1), [], [(3, 0), [], [(10, 1), [(9, 0), [(8, 1),
                                                                   [(7, 0),
                                                                    [(6, 1)],
                                                                    []], []],
                                                          []], []]]]]],
    [3, [(1, 0), [], [(2, 1), [], [(3, 1), [], [(10, 0), [(9, 1), [(8, 1),
                                                                   [(7, 0),
                                                                    [(6, 1)],
                                                                    []], []],
                                                          []], []]]]]],
    [1, [(16, 0), [(8, 0), [(4, 0), [(2, 0), [(1, 0)], [(3, 0)]],
                            [(6, 0), [(5, 0)], [(7, 0)]]],
                   [(12, 0), [(10, 0), [(9, 0)], [(11, 0)]],
                    [(14, 0), [(13, 0)], [(15, 0)]]]], [(24, 0), [(20, 0),
                                                                  [(18, 0),
                                                                   [(17, 0)],
                                                                   [(19, 0)]],
                                                                  [(22, 0),
                                                                   [(21, 0)],
                                                                   [(23, 0)]]],
                                                        [(28, 0),
                                                         [(26, 0), [(25, 0)],
                                                          [(27, 0)]],
                                                         [(30, 0), [(29, 0)],
                                                          [(31, 0)]]]]]],
    [2, [(16, 0), [(8, 1), [(4, 0), [(2, 1), [(1, 0)], [(3, 0)]],
                            [(6, 1), [(5, 0)], [(7, 0)]]],
                   [(12, 0), [(10, 1), [(9, 0)], [(11, 0)]],
                    [(14, 1), [(13, 0)], [(15, 0)]]]], [(24, 1), [(20, 0),
                                                                  [(18, 1),
                                                                   [(17, 0)],
                                                                   [(19, 0)]],
                                                                  [(22, 1),
                                                                   [(21, 0)],
                                                                   [(23, 0)]]],
                                                        [(28, 0),
                                                         [(26, 1), [(25, 0)],
                                                          [(27, 0)]],
                                                         [(30, 1), [(29, 0)],
                                                          [(31, 0)]]]]]],
    [3, [(16, 0), [(8, 1), [(4, 1), [(2, 0), [(1, 1)], [(3, 1)]],
                            [(6, 0), [(5, 1)], [(7, 1)]]],
                   [(12, 1), [(10, 0), [(9, 1)], [(11, 1)]],
                    [(14, 0), [(13, 1)], [(15, 1)]]]], [(24, 1), [(20, 1),
                                                                  [(18, 0),
                                                                   [(17, 1)],
                                                                   [(19, 1)]],
                                                                  [(22, 0),
                                                                   [(21, 1)],
                                                                   [(23, 1)]]],
                                                        [(28, 1),
                                                         [(26, 0), [(25, 1)],
                                                          [(27, 1)]],
                                                         [(30, 0), [(29, 1)],
                                                          [(31, 1)]]]]]]
]

ib002_trees_children_res = [
    [],
    [[], (7, []), []],
    [[[], (5, []), []], (7, []), []],
    [[[], (5, []), []], (7, []), [[], (9, []), []]],
    [[[], (5, []), []], (7, [5]), []],
    [[[], (5, []), []], (7, [5, 9]), [[], (9, []), []]],
    [[[[], (4, []), []], (5, [4, 6]), [[], (6, []), []]], (7, [5, 9]),
     [[[], (8, []), []], (9, [8, 10]), [[], (10, []), []]]],
    [[[[[[[], (1, []), []], (2, [1]), []], (3, [2]), []], (4, [3]), []],
      (5, [4]), []], (6, [5]), []],
    [[[[[[[], (1, []), []], (2, []), []], (3, []), []], (4, [2]), []], (5, []),
      []], (6, [4]), []],
    [[[[[[[], (1, []), []], (2, []), []], (3, []), []], (4, [2]), []], (5, []),
      [[[], (11, []), []], (12, []), []]], (20, [4, 12, 22]),
     [[[], (22, []), []], (26, []), []]],
    [[], (1, [2]), [[], (2, [3]), [[], (3, [10]), [
        [[[[[], (6, []), []], (7, [6]), []], (8, [7]), []], (9, [8]), []],
        (10, [9]), []]]]],
    [[], (1, [3]), [[], (2, []), [[], (3, [9]), [
        [[[[[], (6, []), []], (7, []), []], (8, []), []], (9, [7]), []],
        (10, []), []]]]],
    [[], (1, [10]), [[], (2, []), [[], (3, []), [
        [[[[[], (6, []), []], (7, []), []], (8, []), []], (9, []), []],
        (10, [7]), []]]]],
    [[[[[[], (1, []), []], (2, [1, 3]), [[], (3, []), []]], (4, [2, 6]),
       [[[], (5, []), []], (6, [5, 7]), [[], (7, []), []]]], (8, [4, 12]),
      [[[[], (9, []), []], (10, [9, 11]), [[], (11, []), []]], (12, [10, 14]),
       [[[], (13, []), []], (14, [13, 15]), [[], (15, []), []]]]],
     (16, [8, 24]), [[[[[], (17, []), []], (18, [17, 19]), [[], (19, []), []]],
                      (20, [18, 22]), [[[], (21, []), []], (22, [21, 23]),
                                       [[], (23, []), []]]], (24, [20, 28]),
                     [[[[], (25, []), []], (26, [25, 27]), [[], (27, []), []]],
                      (28, [26, 30]), [[[], (29, []), []], (30, [29, 31]),
                                       [[], (31, []), []]]]]],
    [[[[[[], (1, []), []], (2, []), [[], (3, []), []]], (4, [1, 3, 5, 7]),
       [[[], (5, []), []], (6, []), [[], (7, []), []]]], (8, []),
      [[[[], (9, []), []], (10, []), [[], (11, []), []]],
       (12, [9, 11, 13, 15]),
       [[[], (13, []), []], (14, []), [[], (15, []), []]]]],
     (16, [4, 12, 20, 28]), [
         [[[[], (17, []), []], (18, []), [[], (19, []), []]],
          (20, [17, 19, 21, 23]),
          [[[], (21, []), []], (22, []), [[], (23, []), []]]], (24, []),
         [[[[], (25, []), []], (26, []), [[], (27, []), []]],
          (28, [25, 27, 29, 31]),
          [[[], (29, []), []], (30, []), [[], (31, []), []]]]]],
    [[[[[[], (1, []), []], (2, []), [[], (3, []), []]], (4, []),
       [[[], (5, []), []], (6, []), [[], (7, []), []]]], (8, []),
      [[[[], (9, []), []], (10, []), [[], (11, []), []]], (12, []),
       [[[], (13, []), []], (14, []), [[], (15, []), []]]]],
     (16, [2, 6, 10, 14, 18, 22, 26, 30]), [
         [[[[], (17, []), []], (18, []), [[], (19, []), []]], (20, []),
          [[[], (21, []), []], (22, []), [[], (23, []), []]]], (24, []),
         [[[[], (25, []), []], (26, []), [[], (27, []), []]], (28, []),
          [[[], (29, []), []], (30, []), [[], (31, []), []]]]]]
]


def ib002_compare_list(lst1, lst2):
    # checking tree structure change
    if len(lst1) == 0:
        if len(lst2) == 0:
            return True, None, [], []
        else:
            return False, None, [], []

    compare_left = ib002_compare_list(lst1[0], lst2[0])
    compare_right = ib002_compare_list(lst1[2], lst2[2])
    if isinstance(lst1[1], tuple) and isinstance(lst2[1], tuple):
        if len(lst1[1][1]) != len(lst2[1][1]):
            return False, lst1[1][0], lst1[1][1], lst2[1][1]
        for i in range(len(lst1[1][1])):
            if lst1[1][1][i] != lst2[1][1][i]:
                return False, lst1[1][0], lst1[1][1], lst2[1][1]
        if compare_left[0] is False:
            return compare_left
        if compare_right[0] is False:
            return compare_right
        return True, None, [], []
    else:
        return False, None, [], []


def ib002_in_order(node):
    output = []
    if node is not None:
        output.append(ib002_in_order(node.left))
        keys = []
        for el in node.green_children:
            keys.append(el.key)
        output.append((node.key, keys))
        output.append(ib002_in_order(node.right))
    return output


def ib002_test_set_green_children():
    failure = False
    print("\n*** Testovani funkce set_green_children: ")

    for i in range(len(ib002_trees_children)):
        tree_check = ib002_make_GB_tree(ib002_trees_children[i])
        original_tree = ib002_make_GB_tree(ib002_trees_children[i])
        set_green_children(tree_check)
        result = ib002_compare_list(ib002_trees_children_res[i],
                                    ib002_in_order(tree_check.root))

        if not result[0]:
            make_graph(original_tree, "set_green_children.dot")
            print("NOK ***\n")
            print("\tStrom, ve kterem se nastavoval seznam zelenych potomku"
                  " je v souboru set_green_children.dot .")

            if result[1] is not None:
                print("\tProblem nastal napriklad v uzlu s klicem %s, kde byl"
                      " ocekavan seznam ukazatelu na uzly s klici %s, "
                      "ale vracen byl seznam ukazatelu na uzly s klici %s."
                      % (result[1], result[2], result[3]))
            elif not ib002_comp_trees(original_tree.root, tree_check.root):
                make_graph(original_tree, "set_green_children_changed.dot")
                print("\tByla detekovana zmena stromu. Menit se ma pouze "
                      "atribut green_children. \n\tZmeneny strom je ulozen "
                      "v souboru set_green_children_changed.dot .")

            failure = True
            break

    if not failure:
        print("OK ***")


ib002_min_trees = [
    [2, []],
    [2, []],
    [2, [(-5, 0)]],
    [2, [(-5, 0), [(-7, 1), [(-8, 0)], [(-6, 0)]],
         [(-3, 1), [(-4, 0)], [(-1, 0)]]]],
    [2, [(-5, 0), [(-7, 1), [(-8, 0)], [(-6, 0)]],
         [(-3, 1), [(-4, 0)], [(-1, 0)]]]],
    [2, [(-5, 0), [(-7, 1), [(-8, 0)], [(-6, 0)]],
         [(-3, 1), [(-4, 0)], [(-1, 0)]]]],
    [2, [(-5, 0), [(-7, 1), [(-8, 0)], [(-6, 0)]],
         [(-3, 1), [(-4, 0)], [(-1, 0)]]]],
    [2, [(-5, 0), [(-7, 1), [(-8, 0)], [(-6, 0)]],
         [(-3, 1), [(-4, 0)], [(-1, 0)]]]],
]

ib002_pl_trees = [
    [3, []],
    [3, [(5, 0)]],
    [3, []],
    [3, []],
    [3, [(1, 0)]],
    [3, [(1, 0), [], [(2, 1), [], [(3, 1), [], [(4, 0)]]]]],
    [1, [(1, 0), [], [(2, 0), [], [(3, 0), [], [(4, 0)]]]]],
    [3, [(5, 0), [(4, 1), [(3, 1)], []], []]]
]

ib002_res_trees = [
    [3, []],
    [3, [(5, 0)]],
    [3, [(-5, 0)]],
    [3, [(-5, 0), [(-7, 1), [(-8, 1)], [(-6, 1)]],
         [(-3, 1), [(-4, 1)], [(-1, 1)]]]],
    [3, [(1, 0), [(-5, 1), [(-7, 1), [(-8, 0)], [(-6, 0)]],
                  [(-3, 1), [(-4, 0)], [(-1, 0)]]], []]],
    [3, [(1, 0), [(-5, 1), [(-7, 1), [(-8, 0)], [(-6, 0)]],
                  [(-3, 1), [(-4, 0)], [(-1, 0)]]],
         [(2, 1), [], [(3, 1), [], [(4, 0)]]]]],
    [1, [(1, 0), [(-5, 0), [(-7, 0), [(-8, 0)], [(-6, 0)]],
                  [(-3, 0), [(-4, 0)], [(-1, 0)]]],
         [(2, 0), [], [(3, 0), [], [(4, 0)]]]]],
    [3, [(5, 0), [(4, 1), [(3, 1), [(-5, 0), [(-7, 1), [(-8, 1)], [(-6, 1)]],
                                    [(-3, 1), [(-4, 1)], [(-1, 1)]]], []], []],
         []]]
]


def ib002_create_dot_files(min_tree_list, pl_tree_list, res_tree, join_tree):
    min_tree_print = ib002_make_GB_tree(min_tree_list)
    make_graph(min_tree_print, "join_minus_tree.dot")
    pl_tree_print = ib002_make_GB_tree(pl_tree_list)
    make_graph(pl_tree_print, "join_plus_tree.dot")
    make_graph(res_tree, "join_result_tree_correct.dot")
    make_graph(join_tree, "join_result_tree_yours.dot")


def ib002_test_join_two_GB_trees():
    failure = False
    print("\n*** Testovani funkce join_two_GB_trees: ")

    for i in range(len(ib002_res_trees)):
        min_tree = ib002_make_GB_tree(ib002_min_trees[i])
        pl_tree = ib002_make_GB_tree(ib002_pl_trees[i])
        res_tree = ib002_make_GB_tree(ib002_res_trees[i])
        join_tree = join_two_GB_trees(min_tree, pl_tree)

        if join_tree is None:
            print("NOK ***\n")
            print("\tVase implementace vraci None misto promenne typu GBTree.")
            failure = True
            break
        if not isinstance(join_tree, GBTree):
            print("NOK ***\n")
            print("\tVase implementace nevraci instanci typu GBTree.")
            failure = True
            break
        if join_tree.g_dist != res_tree.g_dist:
            print("NOK ***\n")
            print("\tParametr 'g_dist' vysledneho stromu neni nastaven "
                  "korektne.\n\tByla ocekavana hodnota %i, ale nastavena je"
                  " hodnota %i." % (res_tree.g_dist, join_tree.g_dist))
            failure = True
            break
        if i == 0:
            if join_tree.root is not None:
                print("NOK ***\n")
                print("\tPri spojovani dvou prazdnych stromu nevznikl "
                      "prazdny strom.")
                failure = True
                break
        elif not ib002_comp_trees(join_tree.root, res_tree.root):
            ib002_create_dot_files(ib002_min_trees[i], ib002_pl_trees[i],
                                   res_tree, join_tree)
            print("NOK ***\n")
            print("\tSpojenim nevznikl ocekavany zelenomodry strom."
                  "\n\tStrom se zapornymi klici je v souboru "
                  "join_minus_tree.dot\n\tStrom s kladnymi klici je v souboru"
                  "join_plus_tree.dot \n\tStrom, ktery vytvorila vase funkce "
                  "je v souboru join_result_tree_yours.dot\n\tKorektni strom,"
                  " ktery mel vzniknout spojenim je v souboru "
                  "join_result_tree_correct.dot")

            failure = True
            break

    if not failure:
        print("OK ***")


# Hlavni funkce volana automaticky po spusteni programu.
# Pokud chcete krome dodanych testu spustit vlastni testy, dopiste je sem.
# Odevzdavejte reseni s puvodni verzi teto funkce.

if __name__ == '__main__':
    ib002_test_is_correct_GB_tree()
    ib002_test_insert_to_GB_tree()
    ib002_test_set_green_children()
    ib002_test_join_two_GB_trees()
