package cz.muni.fi.pb162.hw03;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Patrik Valo
 */
public abstract class CommandAbstract implements Command{
    private String nameOfTable;
    private List<String> columns;
    private List<String> values = new ArrayList<>();
    
    @Override
    public String getName() {
        return nameOfTable;
    }
    
    @Override
    public List<String> getColumns() {
        return columns;
    }

    @Override
    public List<String> getValues() {
        return values;
    }
    
    @Override
    public  boolean everythingIsLoaded(int i, String line) {
        for (; i < line.length(); i++) {
            if (!Character.isSpaceChar(line.charAt(i))) return false;
        }
        return true;
    }
    @Override
    public int loadTableName(int i, String line) {
        StringBuilder name = new StringBuilder();
        while(i < line.length() && !Character.isWhitespace(line.charAt(i))) {
            if (!Character.isLetterOrDigit(line.charAt(i))) {
                return -1;
            }
            
            name.append(line.charAt(i));
            i++;
        }
        nameOfTable = name.toString();
        if (nameOfTable.isEmpty()) {
            return -1;
        }
        if (!correctnessOfName(nameOfTable)) {
        
        }
        return i + 1;
    }

    @Override
    public int loadColumnsNames(int i, String line, boolean parenthesis) {
        columns = new ArrayList<>();
        StringBuilder column = new StringBuilder();

        boolean whitespace = false;
        boolean comma = true;
        
        for(; i < line.length(); i++) {
            
            if (whitespace && !comma) {
                if (line.charAt(i) != ',') break;
            }
            
            if (line.charAt(i) == ',') {
                if (comma) return -1;
                comma = true;
                columns.add(column.toString());
                column = new StringBuilder();
                continue;
            }
            
            if (Character.isWhitespace(line.charAt(i))) {
                whitespace = true;
                continue;
            }
            
            if (line.charAt(i) == ')' && parenthesis) break;
            
            if (!Character.isLetterOrDigit(line.charAt(i))) return -1;
            
            comma = false;
            whitespace = false;
            column.append(line.charAt(i));
        }
        
        if (comma) return -1;
        
        columns.add(column.toString());
        
        return (column.toString().isEmpty() || columns.size() <= 0) ? -1 : i;
    }
    
    private int loadQuoteSequence(int i, String line) {
        StringBuilder value = new StringBuilder();
        
        boolean comma = true;
        boolean quote = false;
        
        for (; i < line.length(); i++) {
            if (line.charAt(i) == ')') break;
            
            if (!quote) {
                switch(line.charAt(i)) {
                    case '\"': if (!comma) return -1;
                               quote = true;
                               break;
                    case ',': if (comma) return -1;
                              comma = true;
                              break;
                    default: if (!Character.isWhitespace(line.charAt(i))) return -1; 
                }
                
                continue;
            }
            
            if (line.charAt(i) == '\"') {
                quote = false;
                values.add(value.toString());
                value = new StringBuilder();
                continue;
            }
            
            value.append(line.charAt(i));
            comma = false;            
        }
        
        if (quote || comma) return -1;
        return i;
    }
    
    @Override
    public int loadColumnsParenthesis(int i, String line, boolean withQuote) {
        if (i >= line.length() || line.charAt(i) != '(') {
            return -1;
        }
        i++;
        if (withQuote) {
            if ((i = loadQuoteSequence(i, line)) == -1) {
                return -1;
            }
        } else {
            if ((i = loadColumnsNames(i, line, true)) == -1) {
                return -1;
            }
        }
        if (i >= line.length() || line.charAt(i) != ')') {
            return -1;
        }
        i++;
        return i;
    }

    @Override
    public int containWord(int i, String line, String word) {
        StringBuilder lineWord = new StringBuilder();
        for (int indexOfForm = 0; indexOfForm < word.length(); indexOfForm++) {
            if (i + indexOfForm >= line.length()) return -1;
            lineWord.append(line.charAt(i + indexOfForm));
        }
        i = i + word.length();

        if (!lineWord.toString().toLowerCase().equals(word)) return -1;
        return i;
    }

    @Override
    public boolean correctnessOfName(String name) {
        if (name.toLowerCase().equals("create")) return false;
        if (name.toLowerCase().equals("table")) return false;
        if (name.toLowerCase().equals("insert")) return false;
        if (name.toLowerCase().equals("into")) return false;
        if (name.toLowerCase().equals("values")) return false;
        if (name.toLowerCase().equals("from")) return false;
        return !name.toLowerCase().equals("drop");
    }
    
    @Override
    public boolean correctnessOfNames(List<String> names) {
        for (String name : names) {
            if (!correctnessOfName(name)) return false;
        }
        return true;
    }


    @Override
    public abstract void execute() throws IOException;

    @Override
    public abstract boolean parser(String line);
    
}
