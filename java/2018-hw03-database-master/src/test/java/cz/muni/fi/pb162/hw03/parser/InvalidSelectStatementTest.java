package cz.muni.fi.pb162.hw03.parser;

import cz.muni.fi.pb162.hw03.BaseTest;
import cz.muni.fi.pb162.hw03.TestUtils;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.io.IOException;
import java.util.Arrays;
import java.util.Collection;

import static cz.muni.fi.pb162.hw03.TestUtils.executeStatements;

/**
 * @author Karel Vaculik
 */
@RunWith(value = Parameterized.class)
public class InvalidSelectStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Missing select keyword", "c from abc;"},
                {"Invalid select keyword", "elec c from abc;"},

                {"Missing columns", "select from abc;"},
                {"Missing columns comma", "select c d from abc;"},
                {"Invalid columns name", "select ?c from abc;"},
                {"Columns start with comma", "select ,c from abc;"},
                {"Columns end with comma", "select c, from abc;"},

                {"Invalid from keyword", "select c fromm abc;"},

                {"Missing table name", "select c from;"},

                {"Missing semicolon", "select c from abc"},
                {"Missing semicolon between statements", "create table abc (c) select c from abc;"},
        });
    }

    @Test
    public void shouldErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.SYNTAX_ERROR, getErrContent());
    }
}
