/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pb162.hw03;

/**
 *
 * @author patrik
 */
public class EmptyLineException extends RuntimeException {

    /**
     * Creates a new instance of <code>EmptyLineException</code> without detail
     * message.
     */
    public EmptyLineException() {
    }

    /**
     * Constructs an instance of <code>EmptyLineException</code> with the
     * specified detail message.
     *
     * @param msg the detail message.
     */
    public EmptyLineException(String msg) {
        super(msg);
    }
}
