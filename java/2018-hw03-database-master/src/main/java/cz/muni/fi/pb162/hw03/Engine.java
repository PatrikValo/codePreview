package cz.muni.fi.pb162.hw03;

import java.io.IOException;

/**
 *
 * @author Patrik Valo
 */
public interface Engine {
    
    /**
     * Metoda ktora spusta cely mechanizmus. Dokial sa nenechadza na konci
     * suboru, nacita prikazy postupne po znakoch az dokial nenacita strednik.
     * Po nacitani stredniku sa kontroluje cely prikaz a rozparuje sa pomocou 
     * lineParser(). Nacitaju sa a skontroluju sa vsetky riadky.
     * Nakoniec sa vykonaju dane prikazy pomocou executeCommands().
     * @throws IOException 
     */
    void startEngine() throws IOException;
    
    /**
     * Metoda skontroluje syntax prikazu.
     * @param line Prikaz bez stredniku
     */
    void lineParser(String line);   
    
    /**
     * Metoda vykona nacitane prikazy
     * @throws IOException 
     */
    void executeCommands() throws IOException;
}
