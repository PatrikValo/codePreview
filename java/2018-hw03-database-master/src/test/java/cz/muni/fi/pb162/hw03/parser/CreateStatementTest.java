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
public class CreateStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Simple create", "create table abc (c);"},
                {"Statement with more columns", "create table abc (c, d, e);"},
                {"Keywords with upper letters", "CReAte tAblE abc (c);"},
                {"Extra whitespaces", " \t\n create \t\n   table  \n\t abc \t\n ( \t\n c \t\n,\t\nd \t\n) \t\n; \t\n"},
        });
    }

    @Test
    public void shouldNotErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.EMPTY_STRING, getErrContent());
    }
}
