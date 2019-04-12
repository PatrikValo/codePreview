package cz.muni.fi.pb162.hw03;

import java.io.IOException;

/**
 *
 * @author Patrik Valo
 */
public class Select extends CommandAbstract{
    @Override
    public void execute() throws IOException {
        Table table = null;
        try {
            table = (Table) Database.getTable(getName());
        } catch (ClassNotFoundException ex) {
        }
        if (table == null) {
            System.err.println("Table " + getName() + " is missing");
            return;
        }
        table.print(getColumns());
    }

    @Override
    public boolean parser(String line) {    
        int i;
        // columns
        if ((i = loadColumnsNames(0, line, false)) == -1) {
            return false;
        }
        // from
        if ((i = containWord(i, line , "from")) == -1) return false;

        // whitespace
        if (i >= line.length() || !Character.isWhitespace(line.charAt(i))) return false;
        i++;

        // name of table
        i = loadTableName(i, line);

        return i != -1 && everythingIsLoaded(i, line);
    }

    
}
