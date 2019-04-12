package cz.muni.fi.pb162.hw03;

import java.io.IOException;
import java.util.List;

/**
 *
 * @author Patrik Valo
 */
public interface Command {
    /**
     * Getter pre meno tabulky
     * @return meno tabulky
     */
    String getName();

    /**
     * Getter pre stlpce
     * @return list stlpcov
     */
    List<String> getColumns();
    
    /**
     * Getter pre hodnoty
     * @return list hodnot
     */
    List<String> getValues();

    /**
     * Metoda skontroluje ci je cely prikaz uz nacitany. Ignoruje medzere.
     * @param i aktualna pozicia v prikazy
     * @param line prikaz
     * @return true - vsetko je uz nacitane
     *         false - inak
     */
    boolean everythingIsLoaded(int i, String line);

    /**
     * Kontroluje syntax miesta kde sa ocakava meno tabulky.
     * @param i aktualna pozicia
     * @param line prikaz
     * @return aktualna pozicia - spravny format mena
     *         -1 - inak
     */
    int loadTableName(int i, String line);

    /**
     * Kontroluje syntax miesta kde sa ocakavaju stlpce. 
     * @param i aktualna pozicia
     * @param line prikaz
     * @param parenthesis ak je metoda volana z loadColumnsParenthesis, nastavi
     * sa true, inak false
     * @return aktualna pozicia - spravna syntax
     *         -1 - inak
     */
    int loadColumnsNames(int i, String line, boolean parenthesis);
    
    /**
     * Kontroluje syntax zatvoriek. Nasledne je volanana prislusna metoda
     * ktora kontroluje stlpce.
     * @param i aktualna pozicia
     * @param line prikaz
     * @param withQuote true, ak chcem kontrolovat stlpce "values"
     * @return aktualna pozicia - spravna syntax
     *         -1 - inak
     */
    int loadColumnsParenthesis(int i, String line, boolean withQuote);
    
    /**
     * Kontroluje syntax miesta kde sa ocakava zadane slovo napr. from alebo
     * values.
     * @param i aktualna pozicia
     * @param line prikaz
     * @param word slovo
     * @return aktualna pozicia - spravna syntax
     *         -1 - inak
     */
    int containWord(int i, String line, String word);
    
    /**
     * Kontroluje ci sa zadane meno nezhoduje s nejakym klucovym slovom prikazu.
     * @param name zadane meno
     * @return true - ak sa meno yhoduje s nejakym klucovym slovom
     *         false - inak
     */
    boolean correctnessOfName(String name);
    
    /**
     * Skontroluje, ci sa v liste nenachadza nejaka hodnota
     * ktorej nazov je rovnaky s nejakym klucovym slovom prikazu.
     * @param names list hodnot
     * @return false - nejaka hodnota je rovnaka s klucovym slovom prikazu
     *         true - inak
     */
    boolean correctnessOfNames(List<String> names);
    
    /**
     * Vykona prikaz.
     * @throws IOException 
     */
    void execute() throws IOException;
    
    /**
     * Vykona sa nacitanie prikazu. Okrem skontrolovania syntaxe tu prebieha 
     * aj doplnkova kontrola mien hodnot, ci sa nezhoduju s nejakym klucovym
     * slovom prikazu. Ak sa nejaky nazov zhoduje s nejakym klucovym slovom
     * prikazu, je vyhodena vynimka.
     * Tato kontrola je vykonana len u prikazu create, respektive
     * na hodnotach ktore su novo vkladane do tabulky a neboli na vstupe v 
     * uvodzovkach.
     * @param line riadok
     * @return true - spravna syntax
     *         false - inak
     */
    boolean parser(String line);
}
