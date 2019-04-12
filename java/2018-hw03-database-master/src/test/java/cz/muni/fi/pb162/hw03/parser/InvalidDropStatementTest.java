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
public class InvalidDropStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Missing drop keyword", "table abc;"},
                {"Invalid drop keyword", "dro table abc;"},

                {"Missing table keyword", "drop abc;"},

                {"Missing table name", "drop table;"},
                {"Invalid table name", "drop table a=bc;"},

                {"Missing semicolon between statements", "drop table abc drop table efg;"},
        });
    }

    @Test
    public void shouldErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.SYNTAX_ERROR, getErrContent());
    }
}
