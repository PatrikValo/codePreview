/**
 *
 * @author Patrik Valo
 */
package cz.muni.fi.pb162.project.exception;

/**
 *
 * @author Patrik Valo
 */
public class MissingVerticesException extends RuntimeException {

    /**
     * Constructs an instance of <code>MissingVerticesException</code> with the
     * specified detail message.
     *
     * @param msg the detail message.
     */
    public MissingVerticesException(String msg) {
        super(msg);
    }
    
    /**
     * Constructs an instance of <code>MissingVerticesException</code> with the
     * specified detail message and cause.
     *
     * @param msg the detail message.
     * @param cause the detail cause
     */
    public MissingVerticesException(String msg, Throwable cause) {
        super(msg, cause);
    }
}
