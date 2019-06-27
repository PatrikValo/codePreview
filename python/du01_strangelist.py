#!/usr/bin/python3


# IB002 Domaci uloha 1.
#
# Vasi ulohou v tomto priklade je modifikovat jiz existujici strukturu
# oboustranne zretezeneho linearniho seznamu.
#
# Oboustranne zretezeny seznam ma atribut first, ktery ukazuje na zacatek
# seznamu, a atribut last, ktery ukazuje na konec seznamu.
#
# Kazdy uzel v seznamu ma tri atributy (value, next a prev). Vlastni seznam
# s hodnotami a, b, c, d, e, f vypada bezne takto (v nakresu vynechavame
# atribut first ukazujici na a a atribut last ukazujici na f):
#       ___   ___   ___   ___   ___
#      /   \ /   \ /   \ /   \ /   \
#     a <-- b <-- c <-- d <-- e <-- f
#
# kde obloucky nad pismeny reprezentuji dopredne sipky (napr. a --> b),
# tedy atributy next.
#
# Nas modifikovany StrangeList pouziva pro reprezentaci stejne promenne,
# pouze atributy ukazuji jinam. Atributy next budou ukazovat ob jeden
# uzel, atributy prev zustanou zachovany. Po prevedeni predchoziho
# seznamu na StrangeList vznikne takovyto seznam (opet vynechavame
# atributy first a last):
#       _________   _________
#      /         \ /         \
#     a <-- b <-- c <-- d <-- e <-- f
#            \_________/ \_________/
#
# StrangeList take obsahuje atribut first, ktery ukazuje na jeho zacatek,
# a atribut last, ktery ukazuje na jeho konec, v tomto pripade:
# first - a, last - f.


# Ukol 1.
# Definujte datovou strukturu StrangeList.
# Muzete se inspirovat definici ze zakladniho domaciho ukolu.

class Node:
    def __init__(self):
        self.value = None
        self.next = None
        self.prev = None
        
class StrangeList:
    def __init__(self):
        self.first = None
        self.last = None

# Ukol 2.
# Implementujte metodu list_to_strange_list, ktera z oboustranne
# zretezeneho seznamu vytvori nas StrangeList, tj. upravi atributy next.
# Reprezentaci oboustranne zretezeneho seznamu muzete prevzit ze
# zakladniho domaciho ukolu.

def list_to_strange_list(linkedList):
    """
    vstup: 'linkedList' korektni seznam typu LinkedList
    vystup: stejny seznam s upravenymi atributy next, aby to byl koretni
            StrangeList
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu 'linkedList'
    """
    if linkedList.first == None:        # ak obdrzim prazdny zoznam
        return linkedList
    if linkedList.first.next != None:   # ak ma zoznam viac ako jeden uzel
        pos = linkedList.first.next     # zacinam od 2 uzlu
        while pos != linkedList.last:   # prechadzam vsetky uzle
            pos.prev.next = pos.next    
            pos = pos.next
        pos.prev.next = None            # predposledny uzol nema ziaden next
        return linkedList
    else:                               # inak vrati zoznam s jednym uzlom
        return linkedList


# Ukol 3.
# Implementujte metodu check_strange_list, ktera zkontroluje, ze atributy
# first a last jsou nastaveny spravne. Korektnost next a prev muzete
# predpokladat.

def check_strange_list(strangeList):
    """
    vstup: 'strangeList' typu StrangeList s korektnimi atributy next a prev
    vystup: True, pokud jsou v 'strangeList' atributy first a last nastaveny
            korektne
            False, jinak
    casova slozitost: O(1)
    """
    if strangeList.first != None and strangeList.last != None:
        if strangeList.first.prev != None:
            return False
        if strangeList.last.next != None:
            return False
        if strangeList.last.prev != None:
            if strangeList.last.prev.next != None and\
        strangeList.last.prev.next != strangeList.last :
                return False
        return True
    else:
        if strangeList.first == None and strangeList.last == None:
            return True
        else:
            return False

    
