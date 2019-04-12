package cz.muni.fi.pb162.hw03;

import org.junit.Assert;
import org.junit.Test;

import java.io.IOException;

/**
 * @author Karel Vaculik
 */
public class ErrorLogTest extends BaseTest {

    @Test
    public void createExistingTable() throws IOException {
        TestUtils.executeStatements("create table abc (c); create table abc (d);");

        Assert.assertEquals(TestUtils.getDuplicateTableMessage("abc"), getErrContent());
    }

    @Test
    public void dropMissingTable() throws IOException {
        TestUtils.executeStatements("drop table abc;");

        Assert.assertEquals(TestUtils.getMissingTableMessage("abc"), getErrContent());
    }

    @Test
    public void insertIntoMissingTable() throws IOException {
        TestUtils.executeStatements("insert into tt (c) values (\"v\");");

        Assert.assertEquals(TestUtils.getMissingTableMessage("tt"), getErrContent());
    }

    @Test
    public void selectFromMissingTable() throws IOException {
        TestUtils.executeStatements("select c from tab;");

        Assert.assertEquals(TestUtils.getMissingTableMessage("tab"), getErrContent());
    }
}
