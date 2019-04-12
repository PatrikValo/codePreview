package cz.muni.fi.pb162.project.utils;

import cz.muni.fi.pb162.project.geometry.Polygon;

/**
 *
 * @author Patrik Valo
 */
public class SimpleMath {
    /**
     * Vyrata minimum medzi x suradnicami
     * @param polygon polygon
     * @return minimum
     */
    public static double minX(Polygon polygon) {
        double min = Double.POSITIVE_INFINITY;
        for (int i = 0; i < polygon.getNumVertices(); ++i) {
            if (polygon.getVertex(i).getX() < min) {
                min = polygon.getVertex(i).getX();
            }
        }
        return min;
    }
    /**
     * Vyrata minimum medzi y suradnicami
     * @param polygon polygon
     * @return minimum
     */
    public static double minY(Polygon polygon) {
        double min = Double.POSITIVE_INFINITY;
        for (int i = 0; i < 3; ++i) {
            if (polygon.getVertex(i).getY() < min) {
                min = polygon.getVertex(i).getY();
            }
        }
        return min;
    
    }
    /**
     * Vyrata maximum medzi x suradnicami
     * @param polygon trojuholnik
     * @return maximum
     */
    public static double maxX(Polygon polygon) {
        double max = Double.NEGATIVE_INFINITY;
        for (int i = 0; i < 3; ++i) {
            if (polygon.getVertex(i).getX() > max) {
                max = polygon.getVertex(i).getX();
            }
        }
        return max;
    }
    /**
     * Vyrata maximum medzi y suradnicami
     * @param polygon trojuholnik
     * @return maximum
     */
    public static double maxY(Polygon polygon) {
        double max = Double.NEGATIVE_INFINITY;
        for (int i = 0; i < 3; ++i) {
            if (polygon.getVertex(i).getY() > max) {
                max = polygon.getVertex(i).getY();
            }
        }
        return max;
    }
    
}
