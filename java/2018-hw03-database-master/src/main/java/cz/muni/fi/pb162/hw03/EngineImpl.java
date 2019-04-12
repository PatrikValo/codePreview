package cz.muni.fi.pb162.hw03;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Patrik Valo
 */
public class EngineImpl implements Engine{
    private BufferedReader input;
    private List<Command> commands = new ArrayList<>();
    
    /**
     * Konstruktor pre EngineImpl
     * @param input 
     */
    public EngineImpl(BufferedReader input) {
        this.input = input;
    }
    
    /**
     * Nahradi vsetky biele znaky obycajnou medzerou. Nadbytocne medzery su zmazane. Ak narazi
     * na uvodzovky, obsah medzi nimi sa nemaze ani nenahradzuje, pretoze s velkou
     * pravdepodobnosotu ide nazov
     * @param line
     * @return prikaz bez zbytocnych medzier
     */
    private String removeWhitespaces(String line) {
        
        StringBuilder returnString = new StringBuilder();
        char lastChar = ' ';
        boolean itWasQuote = false;
        
        for (int i = 0; i < line.length(); i++) {
            if (line.charAt(i) == '\"') {
                lastChar = line.charAt(i);
                itWasQuote = !itWasQuote;
                returnString.append(line.charAt(i));
                continue;
            }
            if (itWasQuote) {
                returnString.append(line.charAt(i));
                continue;
            }
            if (Character.isWhitespace(line.charAt(i)) && Character.isWhitespace(lastChar)) {
                continue;
            }
            if (Character.isWhitespace(line.charAt(i))) {
                lastChar = ' ';
                returnString.append(lastChar);
                continue;
            }
            lastChar = line.charAt(i);
            returnString.append(lastChar);
        }
        
        return returnString.toString();
    }
    
    private boolean validation(String name, String body) {
        if (name.equals("create table")) {
            commands.add(new Create());
            return commands.get(commands.size() - 1).parser(body);
        }
        
        if (name.equals("drop table")) {
            commands.add(new Drop());
            return commands.get(commands.size() - 1).parser(body);
        }
        
        if (name.equals("insert into")) {
            commands.add(new Insert());
            return commands.get(commands.size() - 1).parser(body);
        }
        
        if (name.equals("select")) {
            commands.add(new Select());
            return commands.get(commands.size() - 1).parser(body);
        }
        return false;
    }
    
    private int divide(String line) {
        StringBuilder name = new StringBuilder();
        int divideIndex = 0;
        // load command name
        for (int i = 0; i < line.length(); i++) {
            divideIndex = i;
            
            if (Character.isWhitespace(line.charAt(i))) {
                String word = name.toString().toLowerCase();
                if (word.equals("create") || word.equals("insert") || word.equals("drop")) {
                   name.append(" ");
                   continue;
                }
                // Find end of command name
                break;
            }
            
            if (!Character.isLetterOrDigit(line.charAt(i))) {
                throw new IllegalArgumentException("Syntax error");
            }
            
            name.append(line.charAt(i));
        }
        
        return divideIndex; 
    }
    
    @Override
    public void lineParser(String line) {
        // Remove all useless whitespaces

        line = removeWhitespaces(line);

        if (line.isEmpty()) {
            throw new EmptyLineException("Empty Line");
        }

        int divideIndex = divide(line);

        String nameOfCommand = line.substring(0, divideIndex).toLowerCase();

        // At divideIndex line contains whitespace
        if (divideIndex + 1 >= line.length()) {
            // Body of command contains only whitespace
            throw new IllegalArgumentException("Syntax error");
        } else {
            divideIndex++;
        }

        String bodyOfCommand = line.substring(divideIndex, line.length());
        
        if (!validation(nameOfCommand, bodyOfCommand)) {
            throw new IllegalArgumentException("Syntax error");
        }
        
    }

    @Override
    public void executeCommands() throws IOException {
        for (Command actualCommand : commands) {
            actualCommand.execute();
        }
    }
    
    @Override
    public void startEngine() throws IOException {
        StringBuilder line = new StringBuilder();
        int value;

        while ((value = input.read()) != -1) {
            if (value == ';') {
                // End of line
                try {
                    lineParser(line.toString());
                } catch (EmptyLineException e) {
                    // Empty line is OK but there is nothing to execute (executeCommand())
                } catch (IllegalArgumentException e) {
                    // Syntax error
                    throw e;
                }
                // new line
                line = new StringBuilder();
            } else {
                line.append((char) value);
            }
        }
        
        if (!removeWhitespaces(line.toString()).isEmpty()) {
            throw new IllegalArgumentException("Syntax error");
        }
        
        executeCommands();
    }  
}
