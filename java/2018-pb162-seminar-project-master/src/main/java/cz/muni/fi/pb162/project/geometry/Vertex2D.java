package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Patrik Valo
 */
public class Vertex2D implements Comparable<Vertex2D>{

    private final double x;
    private final double y;
    /**
     * 
     * @param x - x-ova suradnica
     * @param y - y-ova suradnica
     */
    public Vertex2D(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }
    
    /**
     * Funkcia, ktora zisti vzdialenost dvoch vrcholov
     * @param vertex - vrchol
     * @return vzdialenost ak druhy vrchol nie je null
     *         -1, inak
     */
    public double distance(Vertex2D vertex) {
        if (vertex == null) {
            return -1;
        }
        double x2 = vertex.getX();
        double y2 = vertex.getY();
        return Math.sqrt(Math.pow((x2 - x), 2) + Math.pow((y2 - y), 2));
    }
    @Override
    public String toString() {
        return "[" + x + ", " + y + "]";
    }
    /**
     * 
     * @param otherVertex - druhy vrchol
     * @return - vrati stred medzi dvomi vrcholmi
     */
    public Vertex2D createMiddle(Vertex2D otherVertex) {
        return new Vertex2D(
                (this.x + otherVertex.getX())/2,
                (this.y + otherVertex.getY())/2
        );
    }
    
    @Override
    public boolean equals(Object o){
        if (o == null || o.getClass() != getClass()) return false;
        Vertex2D vertex = (Vertex2D) o;
        return Double.compare(x, vertex.getX()) == 0 &&
               Double.compare(y, vertex.getY()) == 0;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 19 * hash + Double.hashCode(x);
        hash = 19 * hash + Double.hashCode(y);
        //hash = 47 * hash + (int) (Double.doubleToLongBits(this.x) ^ (Double.doubleToLongBits(this.x) >>> 32));
        //hash = 47 * hash + (int) (Double.doubleToLongBits(this.y) ^ (Double.doubleToLongBits(this.y) >>> 32));
        return hash;
    }

    @Override
    public int compareTo(Vertex2D arg) {
        int diff = Double.compare(this.x, arg.x);
        if (diff == 0) {
            return Double.compare(this.y, arg.y);
        }
        return diff;
    }
}
