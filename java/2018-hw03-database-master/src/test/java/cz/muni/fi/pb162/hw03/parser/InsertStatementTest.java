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
public class InsertStatementTest extends BaseTest {

    @Parameterized.Parameter()
    public String testName;

    @Parameterized.Parameter(value = 1)
    public String input;

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {
                {"Simple insert", "create table abc (c); insert into abc (c) values (\"v\");"},
                {
                    "Insert into more columns",
                    "create table abc (c, d, e); insert into abc (c, d, e) values (\"v\",\"v\",\"v\");"
                },
                {
                    "Extra whitespaces",
                    "create table abc (c,d);\t\n insert \ninto\t abc \t\n(  c ,\n d \t\n) \nvalues \t( \t\n\"v\" \n, \t \"v\" \t\n)\n; "
                },
                {"Special signs in value", "create table abc (c); insert into abc (c) values (\" \tv._&#(:'\");"},
                {
                    "Upper letters and digits in names",
                    "create table 31Ab2C (c1, D); insert into 31Ab2C (c1, D) values (\"v\", \"v\");"
                },
        });
    }

    @Test
    public void shouldNotErrorLog() throws IOException {
        executeStatements(input);

        Assert.assertEquals(TestUtils.EMPTY_STRING, getErrContent());
    }
}
