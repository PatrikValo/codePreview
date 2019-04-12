package cz.muni.fi.pb162.hw03;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * @author Karel Vaculik
 */
public class TestUtils {
    public static final String LINE_SEP = System.getProperty("line.separator");
    public static final String EMPTY_STRING = "";

    public static final String HELP = "usage: java -jar database.jar <path/to/statements_file.txt> <path/to/tables_folder>" + LINE_SEP;
    public static final String SYNTAX_ERROR = "Syntax error" + LINE_SEP;

    private static final String TEST_FILE_PATH = "src/test/resources/test-input.txt";
    private static final String TEST_TABLES_PATH = "src/test/resources/test-tables";
    private static final String GIT_KEEP_FILE_NAME = ".gitkeep";

    private static File testInputFile = new File(TEST_FILE_PATH);
    private static File testTablesFolder = new File(TEST_TABLES_PATH);

    public static void executeStatements(String statements) throws IOException {
        executeStatements(statements, TEST_TABLES_PATH);
    }

    public static void executeStatements(String statements, String tablesPath) throws IOException {
        try(BufferedWriter br = new BufferedWriter(new FileWriter(testInputFile))) {
            br.write(statements);
            br.flush();
        }

        Main.main(new String[]{TEST_FILE_PATH, tablesPath});
    }

    public static void clearTestTablesFolder() {
        File[] files = testTablesFolder.listFiles();

        if (files == null) {
            return;
        }

        for(File file : files) {
            if (!file.getName().equals(GIT_KEEP_FILE_NAME)) {
                file.delete();
            }
        }
    }

    public static String getDuplicateTableMessage(String tableName) {
        return "Table " + tableName + " already exists" + LINE_SEP;
    }

    public static String getMissingTableMessage(String tableName) {
        return "Table " + tableName + " is missing" + LINE_SEP;
    }
}
