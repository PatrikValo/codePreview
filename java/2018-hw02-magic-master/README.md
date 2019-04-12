﻿# Domáca úloha č. 2 - Magic the Gathering

**Zverejnenie úlohy:** 5. 11. 2018

**Deadline:** 23. 11. 2018 23:59

## Predpoklady

Pre úspešnú implementáciu musíte poznať:

* Vytváranie tried, koštruktor
* Rozdiel medzi triedou a objektom
* Prepisovanie metód
* Výnimky
* Práca s kolekciami
* equals() hashcode()
* Rozhrania (vytváranie a implementacia)
* Základné princípy dedičnosti

## Štruktúra projektu

1. Balíček ```magicthegathering``` obsahuje main a aplikačnú logiku
  - **Prosím nemodifikujte žiadnu z týchto tried**
2. Balíček ```magicthegathering.game``` obsahuje triedy a rozhrania, ktoré sú súčasťou zadania
  - **Prosím nemodifikujte žiadnu z týchto tried**
3. Package  ```magicthegathering.impl``` bude obsahovat Vašu implementáciu
  - **Čokoľvek mimo tohto balíčku bude pri hodnotení ignorované**

## Kompilácia projektu

Projekt môžte mimo vývojového prostredia skompilovať pomocou nasledujúceho príkazu:

```bash
mvn clean install -Dcheckstyle.fail=true
```
## Magic the Gathering 

V tomto projekte budete implementovať zjednodušenú hru _Magic the Gathering_.
V [zložke `doc` nájdete príručku s popisom pravidiel hry](doc/MagicTheGathering-QuickStartGuide.pdf), 
ktoré slúžia na objasnenie pravidiel. Ďalej Vám môže orientačne pomôcť nasledujúce video [How to play](https://www.youtube.com/watch?v=RZyXU1L3JXk),
 kde sa vysvetlujú pravidla hry, avšak naša verzia bude o čosi zjednodušená.

_Magic the Gathering_ je kartová hra pre dvoch hráčov, kde sa po každom kole hráči striedajú.
Každý hráč má 20 životov a má k dispozícii karty typu _land_ a _creature_.
Karta typu land predstavuje predstavuje krajinu, ktorá generuje určitý typ many.
V príručke na str. 4 nájdete priradenie jednotlivých typov landov (Plains, Swamp, ...) k jednotlivým typom many (viď. obr.).
Bezfarebnú manu v našom magicku nepoužívame. Rovnako nepoužívame iné typy kariet, či vlastnosti príšer. 
 
![land types](https://i.imgur.com/8ed4dNO.png)

Za manu, ktorú produkuje land, je možné si potom "kúpiť" či vyvolať požadovanú príšeru.
Každá príšera má svoju cenu (cost), meno, power (silu útoku) a toughness (silu obrany).
Hráči môžu prostredníctvom príšer útočiť na súpera, ktorý sa buď ubráni svojimi príšerami, alebo príde o svoje životy.
Platba manou za príšeru laebo útok príšery sa robí pomocou tzv. "tapnutia" karty 
(v reálnej hre sa karta na stole obráti o 90°).
Tapnutie znamená, že karta už je v momentálnom ťahu použitá a nemožno ju v danom ťahu použiť znova.
Okrem operácie tap/untap majú príšery ešte špeciálny atribút zvaný _summoning sickness_.
Po vyložení na stôl "ochorejú" a útočiť môžu až v ďalšom kole. Príšery so summoning sickness však môžu hráča brániť. 

Pre zjednodušenie hry nemáme žiaden balíček, všetky svoje karty má hráč od začiatku na ruke a postupne ich vykladá.

## Priebeh jedného kola

### 0. Príprava na kolo
Hráč untapne všetky svoje karty a zruší summoning sickness u všetkých svojich príšer.

### 1. Fáza vyloženia landu
Hráč môže vyložiť na stôl jednu zo svojim kariet typu land (voľba závisí na hráčovi).

### 2. Fáza povolávania príšer
Hráč si vyberie príšeru, ktorú by chcel vyložiť na stôl.
Ak má hráč na stole dostatok NEtapnutej (nepoužitej) many správneho typu, táto mana bude tapnutá, príšera vyložená na stôl.
Hráč si môže v tomto kole kúpiť viac príšer.

### 3 a. Útok

Útočiaci hráč vyberie ktorými chce útočiť.
Útočiace príšery musia byť NEtaputé a musia byť schopné útoku (nemajú summoning sickness). 

### 3 b. Blokovanie

Oponent (brániaci hráč) vyberie príšery na blokovanie.
Blokovať môžu iba netapnuté príšery. Každá príšera môže útočiť a blokovať iba raz.
### 4. Vyhodnotenie útoku, zranenia

Každá príšera má silu a výdrž(obranu), v nasledujúci obrázkoch bude tento atribút zobrazený takto `power/toughness`.
Ak hráč príšeru neblokoval, príšera mu zoberie toľko životov, aká je jej sila (viď. obr. A).

![attacking a](https://i.imgur.com/75DbHQ8.png)

Ak hráč príšeru blokoval, príšery si vymenia zranenia.
 Ak brániaca príšera ma menšiu výdrž ako útočiaca príšera silu, tak príšera zomrie a absorbuje celý útok príšery (viď. obr. B).

![attacking b](https://i.imgur.com/6fsSi6v.png)

Ak je počet zranení príšery aspoň taký veľký ako jej obrana/výdrž (toughness), tak príšera zomrie (zmizne zo stolu).(viď. obr. C)

![attacking c](https://i.imgur.com/xlUHElH.png)

Hra končí, akonáhle jeden z hráčov umrie, t.j. jeho život klesne na/pod 0


## Implementácia úlohy

Vašou úlohou je postupne implementovať rozhrania popísané nižšie a budú sa nachádzať v balíčku `magicthegathering.impl`.

Úloha obsahuje spustiteľný súbor, ktorý simuluje hru.
Pokiaľ správne implementujete úlohu, mali by ste byť schopní si náš jednoduchý magic reálne zahrať :-)

V každej triede implementujte príslušný konštruktor. Nepoužívajte set metódy, pokiaľ nie sú uvedené v rozhraniach.

### Krok 1: Implementujte `LandCard` a `CreatureCard` 

Triedy _CreatureCardImpl_ a _LandCardImpl_ dedia z `AbstractCard` a slúžia k uchovávaniu stavových informácií o sebe.
Konštruktor _CreatureCardImpl_ bude obsahovať tieto parametre (v rovnakom poradí):
 - `String name` - nemôže byť null alebo prázdny String
 - `List<Manatype> cost` (reprezentuje cenu príšery) - nemôže byť null
 - `int power` - musí byť vačšia alebo rovné 0
 - `int toughness`- musí byť vačšia ako 0
 
Konštruktor _LandCardImpl_ bude obsahovať tieto parametre (v rovnakom poradí):
 - `LandCardType landType` - nemôže byť null
 
V prípade že niektoré z uvedených parametrov porušia vyššie uvedené podmienky, tak sa vyvolá výnimka `IllegalArgumentException`.

Metóda `toString()` vráti pre land: `Land <typ landu>, <typ many>`, pričom typ landu je malými písmenami.
 
Metóda `toString()` vráti pre príšeru: `<name> <cost> <power> / <toughness>` + ak príšera nemá summoning sickness,
na koniec reťazca sa pridá ` can attack`, ak je tapnutá, tak ` TAPPED`. 

Vhodne implementujte metódy equals() and hashcode(). 

Dva objekty typu _CreatureCardImpl_ sa rovnajú v prípade že ich name, cost, power a toughness sú rovnaké.
Dva objekty typu _LandCardImpl_ sa rovnajú v prípade že ich landType sú rovnaké.
### Step 2:  `PlayerImpl`

Trieda _PlayerImpl_ obsahuje ako stavové informácie, tak aj značnú časť hernej logiky či správu stavu hráča.

Konštruktor _PlayerImpl_ bude obsahovať tieto parametre (v rovnakom poradí):
 - `String name`  - nemôže byť null alebo prázdny String
 
V prípade že niektoré z uvedených parametrov porušia vyššie uvedené podmienky, tak sa vyvolá výnimka `IllegalArgumentException`.

Metóda `toString()` vráti meno hráča a v zátvorke počet jeho životov, napr. `Marek(20)`. 

### Step 3:  `GameImpl`

Trieda _GameImpl_ poskytuje správu hráčov, kôl, útokov a blokov. 

Konštruktor má dva parametre ktoré sú inštanciou Player. Ak je jeden z parametrov null, tak sa vyvolá výnimka `IllegalArgumentException`.

Zároveň by táto trieda mala v metóde `initGame()` vygenerovať karty použitím triedy `Generator`.

Útok a blokovanie príšer je vo forme dvoch listov. 
- Attacking list : `[creature1, creature2]`
  - reprezentuje dve útočiace príšery
- Blocking list : `[ null, creature3]`
  - reprezentuje jednu blokujúcu príšeru
  
 Creature1 is neblokovaná (pretože prvá položka v blocking liste je null) to znamená že útok ide priamo do protihráča.
 Creature2 je blokovanaá (pretože druhá pozícia v blocking liste je nejaká príšera)
  to znamená že útoky si vymenia navzájoma a skontroluje sa či nejaká z nich nezomrie.

![attacking c](https://i.imgur.com/xlUHElH.png)

## Hints

- Vytvorte si pomocné metódy ktoré filtrujú karty na základe typu (LandCard, CreatureCard)
- Použite v nich `instanceof`.
- Prečítajte si javadoc v rozhraniach


