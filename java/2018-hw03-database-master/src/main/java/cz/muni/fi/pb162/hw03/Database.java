package cz.muni.fi.pb162.hw03;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 *
 * @author Patrik Valo
 */
public class Database {
    private static File folder;

    /**
     * Nastavi adresar database
     * @param folder adresar
     */
    public static void setFolder(File folder) {
        Database.folder = folder;
    }
    
    /**
     * Vrati tabulku s prislusnym menom. Ak tabulka neexistuje popripade nastene
     * ina chyba vyhodi sa prislusna vynimka
     * @param name meno tabulky
     * @return vrati tabulku
     * @throws IOException vynimka
     * @throws ClassNotFoundException 
     */
    public static Object getTable(String name) throws IOException, ClassNotFoundException {
        File file = new File(folder, name);
        if (!file.exists()) {
            return null;
        }
       
        try (FileInputStream in = new FileInputStream(file);
             ObjectInputStream input = new ObjectInputStream(in)) {
            return input.readObject();
        }
    }
    
    /**
     * Vlozi do databaze tabulku. AK nastane chyba vyhodi sa prislusna vynimka.
     * @param table meno tabulky
     * @return false - ak neexistuje tabulka s danym menom
     *         true - inak
     * @throws IOException 
     */
    public static boolean insertTable(Table table) throws IOException {
        File file = new File(folder, table.getName());
        if (file.exists()) {
            return false;
        } else {
            file.createNewFile();
        }
        try (FileOutputStream out = new FileOutputStream(file);
             ObjectOutputStream output = new ObjectOutputStream(out)) {
            output.writeObject(table);
        }
        return true;
    }
    
    /**
     * Zmaze tabulku z databaze. Ak neexistovala vrati false.
     * @param name meno tabulky
     * @return false - aak neexistovala tabulka s danym menom.
     *         true - ak sa podarila odstranit
     */
    public static boolean deleteTable(String name) {
        File file = new File(folder, name);
        if (!file.exists()) {
            return false;
        }
        file.delete();
        return true;
    }
    
}
