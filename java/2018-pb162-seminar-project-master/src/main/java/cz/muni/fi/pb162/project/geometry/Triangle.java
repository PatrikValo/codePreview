package cz.muni.fi.pb162.project.geometry;

import java.util.Arrays;

/**
 * 
 * @author Patrik Valo 
 */
public class Triangle extends ArrayPolygon{
    private final Triangle[] triangles = new Triangle[3];
    public static final double CONST = 0.001;
    
    /**
     * Konstruktor s parametrami
     * @param a - prvy vrchol
     * @param b - druhy vrchol
     * @param c - treti vrchol
     */
    public Triangle(Vertex2D a, Vertex2D b, Vertex2D c) {
        super(new Vertex2D[]{a,b,c});        
    }
    
    /**
     * Konstruktor s parametrami
     * @param a - prvy vrchol
     * @param b - druhy vrchol
     * @param c - treti vrchol
     * @param depth - hlbka rekurzie
     */
    public Triangle(Vertex2D a, Vertex2D b, Vertex2D c, int depth) {
        this(a, b, c);
        this.divide(depth);
    }
    private boolean isInRange(int index) {
        return (index >= 0 && index <= 2);
    }
    /**
     * Metoda, ktora zisti, ci je trojuholnik rovnostranny
     * @return - true, ak je rovnostranny
     *         - false, inak
     */
    public boolean isEquilateral() {
        double a = getVertex(0).distance(getVertex(1));
        double b = getVertex(0).distance(getVertex(2));
        double c = getVertex(1).distance(getVertex(2));
        return Math.abs(a - b) < CONST && 
               Math.abs(a - c) < CONST &&
               Math.abs(b - c) < CONST;
    }
    
    /**
     * 
     * @return - vrati, ci je dany trojuholnik uz rozdeleny na mensie 
     */
    public boolean isDivided() {
        return triangles[0] != null;
    }
    /**
     * 
     * @param index - pozicia podtrujuhelnika
     * @return - vrati index-ty podtrojuhelnik
     */
    public Triangle getSubTriangle(int index) {
        if (isInRange(index)) {
            return triangles[index];
        }
        return null;
    }
    /**
     * 
     * @return - true ak sa podarilo rozdelit trojuholnik, inak false 
     */
    public boolean divide() {
        if(isDivided()) {
            return false;
        }
        Vertex2D a = getVertex(0).createMiddle(getVertex(1));
        Vertex2D b = getVertex(0).createMiddle(getVertex(2));
        Vertex2D c = getVertex(1).createMiddle(getVertex(2));
        triangles[0] = new Triangle(getVertex(0), a, b);
        triangles[1] = new Triangle(getVertex(1), a, c);
        triangles[2] = new Triangle(getVertex(2), b, c);
        return true;
    }
    
    /**
     * Funkcia, ktora rozdeli trojuholnik na podtrojuholniky
     * @param depth - hlbka rekurzie
     * @return - true / false
     */
    public final boolean divide(int depth) {
        if (depth <= 0) {
            return false;
        }
        divide();
        for (int i = 0; i < 3; ++i) {
            triangles[i].divide(depth - 1);
        }
        return true;   
    }
    
    @Override
    public boolean equals(Object o){
        return super.equals(o);
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 83 * hash + Arrays.deepHashCode(this.triangles);
        return hash;
    }
    
    
    
}
