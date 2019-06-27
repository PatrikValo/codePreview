#!/usr/bin/python3


# IB002 Domaci uloha 2.
#
# Jednosmerne spojovany seznam znate z prednasky - jde o zretezeny seznam
# uzlu (Node), kde kazdy uzel ukazuje na sveho naslednika. V tomto prikladu
# nemame first a last, seznam je zadany "prvnim" ze svych uzlu.
#
# Tato uloha pracuje se dvema typy jednosmerne spojovanych seznamu:
# Linearni seznam - kde posledni prvek seznamu ukazuje na None.
# Kruhovy seznam - kde posledni prvek seznamu ukazuje zpet na prvni prvek.
#
# Pro vsechny funkce muzete predpokladat, ze seznam na vstupu je linearni,
# nebo kruhovy, tj. nemusite napriklad osetrovat situaci, kdy naslednikem
# "posledniho" v seznamu je "druhy".
#
# Do definice tridy Node nijak nezasahujte.

class Node:
    """Trida Node reprezentujici prvek ve spojovanem seznamu

    Atributy:
        key        klic daneho uzlu (cele cislo)
        next       odkaz na dalsi prvek seznamu
        opposite   odkaz na protejsi prvek seznamu, viz ukol 3.
    """

    def __init__(self):
        self.key = 0
        self.next = None
        self.opposite = None


# Ukol 1.
# Implementujte funkci is_circular, ktera dostane prvni uzel seznamu
# a otestuje, zda je zadany zretezeny seznam kruhovy.
# Prazdny seznam neni kruhovy.

def is_circular(node):
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: True, pokud je seznam z uzlu 'node' kruhovy
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    """
    pos = node
    if pos == None:
        return False
    while pos.next != None:
        if pos.next == node:
            return True
        pos = pos.next
    return False


# Ukol 2.
# Implementujte funkci get_length, ktera vrati delku (tj. pocet ruznych uzlu)
# (linearniho nebo kruhoveho) zretezeneho seznamu zacinajiciho v zadanem uzlu.
# Pokud je seznam prazdny (None), vrati 0.

def get_length(node):
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: pocet prvku v zadanem seznamu
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    """
    pos = node
    length = 1
    if pos == None:
        return 0
    while pos.next != None and pos.next != node:
        length = length + 1
        pos = pos.next
    return length


# Ukol 3.
# Implementujte funkci calculate_opposites, ktera korektne naplni atributy
# "opposite" v uzlech kruhoveho seznamu sude delky. Tj. pro kruhove seznamy
# delky 2n naplni u kazdeho uzlu atribut opposite uzlem, ktery je o n kroku
# dale (tedy v kruhu je to uzel "naproti").
#
# Napriklad v kruhovem seznamu 1 -> 2 -> 3 -> 4 (-> 1) je opposite
# uzlu 1 uzel 3, uzlu 2 uzel 4, uzlu 3 uzel 1 a uzlu 4 uzel 2.
#
# Pokud vstupni seznam neni kruhovy nebo ma lichou delku, tak funkce
# calculate_opposites seznam neupravuje.
#
# Pozor na casovou a prostorovou slozitost vaseho algoritmu!

def calculate_opposites(node):
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: nic, kokretne doplni atribut opposite pro seznam sude delky
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    """
    if node != None:
        pos = node
        middle = node
        length = 1
        while pos.next != None and pos.next != node: # dlzka + pozicia middle 
            pos = pos.next
            length += 1
            if length % 2 == 0:
                middle = middle.next
        pos = pos.next
        if pos != None and length % 2 == 0:
            while length > 0:
                pos.opposite = middle
                middle = middle.next
                pos = pos.next
                length -= 1
            


