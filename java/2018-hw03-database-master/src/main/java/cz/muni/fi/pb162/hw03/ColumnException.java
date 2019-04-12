package cz.muni.fi.pb162.hw03;

/**
 *
 * @author Patrik Valo
 */
public class ColumnException extends RuntimeException {

    /**
     * Creates a new instance of <code>ColumnException</code> without detail
     * message.
     */
    public ColumnException() {
    }

    /**
     * Constructs an instance of <code>ColumnException</code> with the specified
     * detail message.
     *
     * @param msg the detail message.
     */
    public ColumnException(String msg) {
        super(msg);
    }
}
