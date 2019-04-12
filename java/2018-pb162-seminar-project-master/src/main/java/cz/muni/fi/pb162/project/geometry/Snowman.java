package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Patrik Valo
 */
public class Snowman {
    public static final int NUMBEROFPOLYGON = 3;
    private final double creator = 0.8;
    
    private final double smaller;
    private final RegularPolygon[] polygons;
    
    /**
     * Konstruktor triedz Snowman
     * @param polygon objekt typu Circumcircle
     * @param smaller cislo medzi (0,1> urcujuce zmensenie gul
     */
    public Snowman(RegularPolygon polygon, double smaller) {
        if (smaller > 1 || smaller <= 0) {
            this.smaller = creator;
        } else {
            this.smaller = smaller;
        }
        polygons = new RegularPolygon[NUMBEROFPOLYGON];
        polygons[0] = polygon;
        fillCircles(polygon);        
    }
    
    private void fillCircles(RegularPolygon last) {
        for (int i = 1; i < polygons.length; ++i) {
            // novy polomer
            double actualRadius = creator * last.getRadius();
            // novy stred kruhu 
            Vertex2D actualCentre = new Vertex2D(last.getCenter().getX(),
            last.getCenter().getY() + last.getRadius() + actualRadius);
            // novy polygon
            polygons[i] = new GeneralRegularPolygon(actualCentre, 
                    last.getNumEdges(), actualRadius);
            last = polygons[i];
        }
    }
    public RegularPolygon[] getBalls() {
        return polygons;
    }
}
