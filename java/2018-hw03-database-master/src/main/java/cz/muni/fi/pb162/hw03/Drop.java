package cz.muni.fi.pb162.hw03;

/**
 *
 * @author Patrik Valo
 */
public class Drop extends CommandAbstract{
    
    @Override
    public void execute() {
        if (!Database.deleteTable(getName())) {
            System.err.println("Table " + getName() + " is missing");
        }
    }

    @Override
    public boolean parser(String line) {
        // name of table
        int i = loadTableName(0, line);

        return i != -1 && everythingIsLoaded(i, line);
    }
    
}
