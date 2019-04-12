package cz.muni.fi.pb162.project.exception;

/**
 *
 * @author Patrik Valo
 */
public class TransparentColorException extends Exception{
    
    /**
     * Constructs an instance of <code>TransparentColorException</code> with the
     * specified detail message.
     *
     * @param msg the detail message.
     */
    public TransparentColorException(String msg) {
        super(msg);
    }
    /**
     * Constructs an instance of <code>TransparentColorException</code> with the
     * specified detail message and cause.
     *
     * @param msg the detail message.
     * @param cause the detail cause
     */
    public TransparentColorException(String msg, Throwable cause) {
        super(msg, cause);
    }
}
