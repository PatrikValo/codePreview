package cz.muni.fi.pb162.project.exception;

/**
 *
 * @author Patrik Valo
 */
public class EmptyDrawableException extends Exception {

    /**
     * Constructs an instance of <code>EmptyDrawableException</code> with the
     * specified detail message.
     *
     * @param msg the detail message.
     */
    public EmptyDrawableException(String msg) {
        super(msg);
    }
    
    /**
     * Constructs an instance of <code>EmptyDrawableException</code> with the
     * specified detail message and cause.
     *
     * @param msg the detail message.
     * @param cause the detail cause
     */
    public EmptyDrawableException(String msg, Throwable cause) {
        super(msg, cause);
    }
}
