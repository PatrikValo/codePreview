package cz.muni.fi.pb162.hw03;

import java.io.IOException;
import java.util.List;
/**
 *
 * @author Patrik Valo
 */
public class Create extends CommandAbstract{
    
    @Override
    public void execute() throws IOException {
        Table table = new Table(getName());
        List<String> columnsNames = getColumns();

        for (String column : columnsNames) {
            table.insertNewColumn(column);
        }
        
        if (!Database.insertTable(table)) {
            System.err.println("Table " + getName() + " already exists");
        }
        
    }

    @Override
    public boolean parser(String line) {
        int i;

        // name of table
        if ((i = loadTableName(0, line)) == -1) return false;

        // columns
        if ((i = loadColumnsParenthesis(i, line, false)) == -1) return false;
        
        // control end of command
        if (everythingIsLoaded(i, line)) {
            
            if(!correctnessOfName(getName()) || !correctnessOfNames(getColumns())) {
                throw new NameException("Command contains same name as keyword of command");
            }
            
            return true;
        }
        return false;
    }
    
}
