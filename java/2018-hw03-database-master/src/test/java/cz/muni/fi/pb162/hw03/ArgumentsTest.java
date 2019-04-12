package cz.muni.fi.pb162.hw03;

import org.junit.Assert;
import org.junit.Test;

import java.io.IOException;

/**
 * @author Karel Vaculik
 */
public class ArgumentsTest extends BaseTest {

    @Test
    public void notEnoughArguments() throws IOException {
        Main.main(new String[1]);

        Assert.assertEquals(TestUtils.HELP, getOutContent());
    }

    @Test
    public void tooMuchArguments() throws IOException {
        Main.main(new String[3]);

        Assert.assertEquals(TestUtils.HELP,getOutContent());
    }

    @Test(expected = IOException.class)
    public void missingInputFile() throws IOException {
        Main.main(new String[]{"src/test/resources/missing-file.txt", "src/test/resources/test-tables"});
    }

    @Test(expected = IOException.class)
    public void missingTablesFolder() throws IOException {
        TestUtils.executeStatements("create table abc (c);", "src/test/resources/missing-folder");
    }
}
