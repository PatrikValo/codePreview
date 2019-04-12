package cz.muni.fi.pb162.hw03;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author Patrik Valo
 */
public class Main {

    /**
     * Main
     * @param args args
     * @throws IOException 
     */
    public static void main(String[] args) throws IOException {

        if (args.length != 2 ) {
            System.out.println("usage: java -jar database.jar <path/to/statements_file.txt> <path/to/tables_folder>");
            return;
        }

        File inputFile = new File(args[0]);
        File outputFile = new File(args[1]);
        if (!inputFile.exists() || !outputFile.exists()) {
            throw new IOException("Unknown Files");
        }
        try(BufferedReader input = new BufferedReader(new FileReader(inputFile))) {
            Database.setFolder(outputFile);
            
            EngineImpl engine = new EngineImpl(input);
            
            // Everything starts here
            engine.startEngine();
                    
        } catch (IllegalArgumentException e) {
            
            System.err.println("Syntax error");
        
        }
    }
}
