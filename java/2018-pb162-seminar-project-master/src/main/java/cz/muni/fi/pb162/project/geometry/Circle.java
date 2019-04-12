package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Patrik Valo
 */
public class Circle extends GeneralRegularPolygon{
    /**
     * Kontruktor bez parametrov
     */
    public Circle() {
        //super(new Vertex2D(0,0), Integer.MAX_VALUE, 1);
        this(new Vertex2D(0,0), 1);
    }
    
    /**
     * Konstruktor s dvomi parametrami
     * @param center - stred kruhu
     * @param radius - polomer kruhu
     */
    public Circle(Vertex2D center, double radius) {
        super(center, Integer.MAX_VALUE, radius);
        super.setColor(Color.RED);
    }
    
    @Override
    public double getEdgeLength(){
        return 0;
    }
    
    @Override
    public String toString() {
        return "Circle: center=[" + super.getCenter().getX() + ", " + 
                super.getCenter().getY() + "], radius=" + super.getRadius();
    }
    
}
