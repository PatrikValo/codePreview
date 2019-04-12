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
public class DropStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Simple drop", "create table abc (c); drop table abc;"},
                {"Keywords with upper letters", "create table abc (c); dROp tAbLE abc;"},
                {"Upper letters and digits in table name", "create table a23BC1 (c); drop table a23BC1;"},
        });
    }

    @Test
    public void shouldNotErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.EMPTY_STRING, getErrContent());
    }
}
