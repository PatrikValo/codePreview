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
public class InvalidCreateStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Missing create keyword", "table abc (c);"},
                {"Invalid create keyword", "cvreate table abc (c);"},

                {"Missing table keyword", "create abc (c);"},
                {"Invalid table keyword", "create tabl abc (c);"},

                {"Missing table name", "create table (c);"},
                {"Invalid table name", "create table ab:c (c);"},

                {"Missing table columns", "create table abc;"},
                {"Missing table columns right parenthesis", "create table abc (c;"},
                {"Missing table columns names", "create table abc ();"},
                {"Missing table columns comma", "create table abc (c d);"},
                {"Table columns start with comma", "create table abc (,c);"},
                {"Table columns end with comma", "create table abc (c,);"},
                {"Table columns with two commas in a row", "create table abc (c,,d);"},

                {"Missing semicolon", "create table abc (c)"},
        });
    }

    @Test
    public void shouldErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.SYNTAX_ERROR, getErrContent());
    }
}
