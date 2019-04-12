package cz.muni.fi.pb162.hw03;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Patrik Valo
 */
public class Table implements Serializable {
    private final String name;
    private Map<String, List<String>> matrix = new HashMap<>();
    private int height = 0; 
    
    /**
     * Konstruktor pre Table
     * @param name meno tabulky
     */
    public Table(String name) {
        this.name = name;
    }
    
    public String getName() {
        return name;
    }
    
    /**
     * Vlozi do tabulky novy stlpec
     * @param name meno stlapca
     */
    public void insertNewColumn(String name) {
        matrix.put(name, new ArrayList<>());
    }
    
    /**
     * Pre dane stlpece vklada hodnoty. Ostatnym stlpcom prida prazdne
     * string. Ak sa pocet sptlcov neyhoduje s poctom hodnot vyhodi sa vynimka.
     * @param names mena stlpcov
     * @param values hodnoty
     */
    public void insertValues(List<String> names, List<String> values) {
        if (names.size() != values.size()) {
            throw new ColumnException("Not same count of columns and values");
        }
        height++;
        for (int i = 0; i < names.size(); i++) {
            if (!matrix.containsKey(names.get(i))) {
                throw new ColumnException("Column not exist");
            }
            matrix.get(names.get(i)).add(values.get(i));
        }
        for (String name : matrix.keySet()) {
            if (!names.contains(name)) {
                matrix.get(name).add("");
            }
        }
    }
    
    /**
     * Vypise hodnoty danych stlpcov.
     * @param names mena stlcov
     */
    public void print(List<String> names) {
        boolean newLine;
        for (int i = 0; i < height; i++) {
            newLine = true;
            for (String name : names) {
                if (!newLine) {
                    System.out.print(";");
                }
                newLine = false;
                System.out.print(matrix.get(name).get(i));
            }
            System.out.print(System.lineSeparator());
        }
    }
    
}
