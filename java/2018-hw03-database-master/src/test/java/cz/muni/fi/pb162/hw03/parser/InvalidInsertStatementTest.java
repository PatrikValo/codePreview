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
public class InvalidInsertStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Invalid insert keyword", "insret into abc (c) values (\"v\");"},

                {"Missing into keyword", "insert abc (c) values (\"v\");"},
                {"Invalid into keyword", "insert in-to abc (c) values (\"v\");"},

                {"Missing table name", "insert into (c) values (\"v\");"},
                {"Invalid table name", "insert into .abc (c) values (\"v\");"},

                {"Missing table columns", "insert into abc values (\"v\");"},
                {"Missing table columns left parenthesis", "insert into abc c) values (\"v\");"},
                {"Missing table columns right parenthesis", "insert into abc (c values (\"v\");"},
                {"Missing table columns comma", "insert into abc (c d) values (\"v\",\"v\");"},
                {"Invalid table columns name", "insert into abc (c*c) values (\"v\");"},
                {"Table columns start with comma", "insert into abc (,c) values (\"v\");"},
                {"Table columns with two commas in a row", "insert into abc (c,,d) values (\"v\",\"v\");"},

                {"Missing values keyword", "insert into abc (c) (\"v\");"},
                {"Invalid values keyword", "insert into abc (c) value (\"v\");"},

                {"Missing values left parenthesis", "insert into abc (c) values \"v\");"},
                {"Missing values right parenthesis", "insert into abc (c) values (\"v\";"},
                {"Missing value", "insert into abc (c) values ();"},
                {"Missing values comma", "insert into abc (c,d) values (\"v\" \"v\");"},
                {"Semicolon in value", "insert into abc (c) values (\"v;\");"},
                {"Quotation marks in value", "insert into abc (c) values (\"v\"\");"},
                {"Values start with comma", "insert into abc (c) values (,\"v\");"},
                {"Values with two commas in a row", "insert into abc (c,d) values (\"v\",,\"v\");"},

                {"Missing semicolon", "insert into abc (c) values (\"v\")"},
                {"Missing semicolon between statements", "create table abc (c) insert into abc (c) values (\"v\");"},
        });
    }

    @Test
    public void shouldErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.SYNTAX_ERROR, getErrContent());
    }
}
