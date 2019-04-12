package cz.muni.fi.pb162.hw03;

import org.junit.Assert;
import org.junit.Test;

import java.io.IOException;

/**
 * @author Karel Vaculik
 */
public class MainTest extends BaseTest {

    @Test
    public void select() throws IOException {
        TestUtils.executeStatements("create table t (a,b);insert into t (a,b) values (\"8\",\"r\");select a,b from t;");

        Assert.assertEquals("8;r" + TestUtils.LINE_SEP, getOutContent());
    }

    @Test
    public void selectSubsetOfColumns() throws IOException {
        TestUtils.executeStatements("create table tab1 (a, b, c);");
        TestUtils.executeStatements("insert into tab1 (a, b, c) values (\"value\", \"13\", \"+-\");");
        TestUtils.executeStatements("select a, c from tab1;");

        Assert.assertEquals("value;+-" + TestUtils.LINE_SEP, getOutContent());
    }

    @Test
    public void insertIntoSubsetOfColumns() throws IOException {
        TestUtils.executeStatements("create table tb (a, b, c, d);");
        TestUtils.executeStatements("insert into tb (b, c) values (\"bcol\", \"ccol\");");
        TestUtils.executeStatements("select a, b, c, d from tb;");

        Assert.assertEquals(";bcol;ccol;" + TestUtils.LINE_SEP, getOutContent());
    }

    @Test
    public void multipleTables() throws IOException {
        TestUtils.executeStatements("create table tb1 (a, b, c, d);");
        TestUtils.executeStatements("create table tb2 (c1, c2);");
        TestUtils.executeStatements("create table tb3 (1, 2, 3);");
        TestUtils.executeStatements("insert into tb3 (1, 2, 3) values (\"val\", \"1\", \"j\");");
        TestUtils.executeStatements("select 1, 2, 3 from tb3;");

        Assert.assertEquals("val;1;j" + TestUtils.LINE_SEP, getOutContent());
    }

    @Test
    public void multipleRowsInTable() throws IOException {
        TestUtils.executeStatements("create table tb (c1, c2);");
        TestUtils.executeStatements("insert into tb (c1, c2) values (\"r11\", \"r12\");");
        TestUtils.executeStatements("insert into tb (c1, c2) values (\"r21\", \"r22\");");
        TestUtils.executeStatements("insert into tb (c1, c2) values (\"r31\", \"r32\");");
        TestUtils.executeStatements("select c2 from tb;");

        String expected = "r12" + TestUtils.LINE_SEP + "r22" + TestUtils.LINE_SEP + "r32" + TestUtils.LINE_SEP;

        Assert.assertEquals(expected, getOutContent());
    }

    @Test
    public void multipleSelects() throws IOException {
        TestUtils.executeStatements("create table tb (c1, c2);");
        TestUtils.executeStatements("insert into tb (c1, c2) values (\"v1\", \"v2\");");
        TestUtils.executeStatements("select c1 from tb;");
        TestUtils.executeStatements("select c1, c2 from tb;");

        Assert.assertEquals("v1" + TestUtils.LINE_SEP + "v1;v2" + TestUtils.LINE_SEP, getOutContent());
    }
}
