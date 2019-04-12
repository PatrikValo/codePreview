package cz.muni.fi.pb162.project.utils;

import cz.muni.fi.pb162.project.geometry.Measurable;
import cz.muni.fi.pb162.project.geometry.Triangle;

/**
 *
 * @author Patrik Valo
 */
public class Gauger {
    /**
     * Vypis vysky a sirky objektu
     * @param object objekt typu Measurable
     */
    public static void printMeasurement(Measurable object) {
        System.out.println("Width: " + object.getWidth());
        System.out.println("Height: " + object.getHeight());
    }
    /**
     * Vypis vysky a sirky trojuholnika
     * @param triangle trojuholnik
     */
    public static void printMeasurement(Triangle triangle) {
        System.out.println(triangle.toString());
        printMeasurement((Measurable)triangle);
    }
    
    
}
