Úloha č. 3: Databáze
====================================

**Zveřejnění úlohy:** 3. prosince 2018

**Deadline pro odevzdání:** 21. prosince 2018

Obecné informace
-------------------
Cílem zadání je vytvořit jednoduchý databázový engine, který bude schopný perzistentně ukládat data do tabulek a
získávat tato data z tabulek zpět. Práce s daty se bude provádět pomocí jednoduchých SQL příkazů.

Maximální počet bodů za tuto úlohu je **11**.

- **6,5 bodu** za procházející testy (přiložené testy negarantují 100% správnost).
- **3,5 bodu** za procházející rozšířené testy (mají k dispozici pouze cvičící).
- **1 bod** za čisté a elegantní řešení (konvence, minimální opakování kódu).

### Zadání
Následující zadání popisuje pouze, jak se má program chovat na základě daného vstupu. Struktura programu, definice tříd
a jejich metod je zcela na vás. **Chování, která nejsou v zadání specifikovaná, se nebudou testovat.** Jak se bude
v takové situaci váš program chovat, je zase zcela na vás.

Vstupní argumenty
---------------------------
- Program bude přijímat vždy dva vstupní argumenty:

  - Cesta k souboru s SQL příkazy, které se mají vykonat.
  - Cesta k adresáři, ve kterém se budou ukládat data.
  
- Pokud počet vstupních parametrů neodpovídá zadání, vypíše program na standardní výstup nápovědu ve tvaru:

```$xslt
usage: java -jar database.jar <path/to/statements_file.txt> <path/to/tables_folder>
```

- V případě, že zdrojový soubor nebo datový adresář není k dispozici, nechá program propadnout výjimku `IOException` a
ukončí se.

>Existenci souboru nebo adresáře lze ověřit pomocí třídy `File` a metody `exists()`.

SQL příkazy
---------------------------
Ve zdrojovém souboru se může nacházet 0 a více SQL příkazů. Jde o zjednodušené varianty s omezeným chováním. Pro všechny
čtyři příkazy platí následující pravidla:

- Klíčová slova příkazů jsou nezávislá na velikosti písmen. Validní je jak `create`, tak i `CREATE` nebo `CREate`.

- Název tabulky nebo sloupce se může skládat z libovolného počtu znaků, které projdou testem metody 
`Character.isLetterOrDigit()`.

- Všechny prvky příkazů mohou být odděleny libovolným počtem bílých znaků. Za bílý znak se považuje vše, co projde
testem metody `Character.isWhitespace()`.

- Pokud není příkaz syntakticky validní, vypíše se na chybový výstup `System.err` zpráva `Syntax error` a ukončí se
běh programu.

>Mezi prvky příkazu se počítají i samostatné znaky, jako jsou závorky, čárka nebo středník.

### CREATE
Vytvoří tabulku s uvedenými sloupci.

```$xslt
CREATE TABLE tableName (columnName1, columnName2, ... );
```

- Obsahuje vždy alespoň jeden sloupec.

- Pokud tabulka s daným názvem už existuje, tak místo vytvoření program vypíše na chybový výstup zprávu

```$xslt
Table <tableName> already exists
```

### DROP
Zahodí existující tabulku.

```$xslt
DROP TABLE tableName;
```

- Pokud tabulka s daným názvem neexistuje, tak se vypíše na chybový výstup zpráva

```$xslt
Table <tableName> is missing
```

### SELECT
Vypíše data zvolených sloupců z tabulky na standardní výstup.

```$xslt
SELECT columnName1, columnName2, ... FROM tableName;
```

- Vždy je uveden alespoň jeden sloupec.

- Výčet sloupců může být i podmnožina definovaných sloupců v tabulce.

- Pro jednoduchost zadání se vypisují vždy všechny záznamy v tabulce. Filtrovat lze tedy pouze sloupce.

- Jeden záznam z tabulky se vypisuje na jeden řádek a jednotlivé hodnoty se oddělují středníkem.

- Pokud tabulka s daným názvem neexistuje, tak se vypíše na chybový výstup zpráva

```$xslt
Table <tableName> is missing
```

>Nový řádek nezávislý na platformě lze získat pomocí `System.lineSeparator()`.

#### Příklad
Nechť je v databázi vytvořená tabulka `table`, která má definované tři sloupce a jsou v ní uložené dva záznamy.
Následující příkaz

```$xslt
SELECT column1, column3 FROM table;
```

potom vypíše na standardní výstup

```$xslt
value11;value13
value21;value23
```

### INSERT
Vloží nový záznam do tabulky podle zvolených sloupců.

```$xslt
INSERT INTO tableName (columnName1, columnName2, ... ) VALUES ("value1", "value2", ... );
```

- Vždy je uveden alespoň jeden sloupec.

- Výčet sloupců může být i podmnožina definovaných sloupců v tabulce. V takovém případě se za chybějící hodnoty doplní
prázdný řetězec.

- Hodnoty jsou uvedeny v uvozovkách a mohou se skládat z libovolných znaků kromě uvozovek a středníku.

- Pokud tabulka s daným názvem neexistuje, tak se vypíše na chybový výstup zpráva

```$xslt
Table <tableName> is missing
```
