package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Patrik Valo
 */
public class Square extends GeneralRegularPolygon{
    /**
     * Konstruktor triedy Square
     * @param center stred
     * @param width priemer
     */
    public Square(Vertex2D center, double width) {
        super(center, 4, width/2);
    }
    /**
     * Kontstruktor triedy Square
     * @param object objekt typu Circumcircle
     */
    public Square(Circumcircle object) {
        this(object.getCenter(), object.getRadius()*2);        
    }
        
    @Override
    public String toString() {
        return ("Square: vertices=[" + 
                super.getVertex(0).getX() + ", " + 
                super.getVertex(0).getY() + "] " + "[" + 
                super.getVertex(1).getX() + ", " +
                super.getVertex(1).getY() + "] " + "[" + 
                super.getVertex(2).getX() + ", " + 
                super.getVertex(2).getY() + "] " + "[" + 
                super.getVertex(3).getX() + ", " + 
                super.getVertex(3).getY() + "]");
    }
    
}
