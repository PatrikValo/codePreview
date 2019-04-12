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
public class SelectStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Simple select", "create table abc (c); select c from abc;"},
                {"Keywords with upper letters", "create table abc (c); SELect c froM abc;"},
                {"Upper letters and digits in names", "create table A2c12b (C4c, 2); select C4c, 2 from A2c12b;"},
        });
    }

    @Test
    public void shouldNotErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.EMPTY_STRING, getErrContent());
    }
}
