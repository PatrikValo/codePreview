package cz.muni.fi.pb162.hw03;

import java.io.IOException;

/**
 *
 * @author Patrik Valo
 */
public class Insert extends CommandAbstract{

    @Override
    public void execute() throws IOException {
        Table table = null;
        try {
            table = (Table) Database.getTable(getName());
        } catch (ClassNotFoundException ex) {
        }
        if (table == null) {
            System.err.println("Table " + getName() + " is missing");
        } else {
            table.insertValues(getColumns(), getValues());
            Database.deleteTable(getName());
            Database.insertTable(table);        
        }
    }

    @Override
    public boolean parser(String line) {
        int i;
        // name of table
        if ((i = loadTableName(0, line)) == -1) return false;

        // columns
        if ((i = loadColumnsParenthesis(i, line, false)) == -1) return false;

        // whitespace
        if (!Character.isWhitespace(line.charAt(i))) return false;
        i++;

        // values
        if ((i = containWord(i, line , "values")) == -1) return false;

        // whitespace
        if (i >= line.length() || !Character.isWhitespace(line.charAt(i))) return false;
        i++;

        // name of values
        if ((i = loadColumnsParenthesis(i, line, true)) == -1) return false;
        return everythingIsLoaded(i, line);
    }
    
}
