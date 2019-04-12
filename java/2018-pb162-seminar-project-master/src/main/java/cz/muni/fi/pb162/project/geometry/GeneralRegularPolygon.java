package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Patrik Valo
 */
public class GeneralRegularPolygon implements RegularPolygon, Colored{
    private final Vertex2D center;
    private final int numberOfEdges;
    private final double radius;
    private Color color = Color.BLACK;
    
    GeneralRegularPolygon(Vertex2D center, int numberOfEdges, double radius) {
        this.center = center;
        this.numberOfEdges = numberOfEdges;
        this.radius = radius;
    }
    
    @Override
    public int getNumEdges(){
        return numberOfEdges;
    }

    @Override
    public double getEdgeLength(){
        return (2*radius*Math.sin((Math.PI/numberOfEdges)));
    }
    
    @Override
    public double getWidth(){
        return 2*radius;
    }
    
    @Override
    public double getHeight(){
        return 2*radius;
    }
    
    @Override
    public Vertex2D getVertex(int index){
        double x = center.getX()-radius*Math.cos(index*2*Math.PI/numberOfEdges);
        double y = center.getY()-radius*Math.sin(index*2*Math.PI/numberOfEdges);
        return new Vertex2D(x, y);
    }
    
    @Override
    public Vertex2D getCenter(){
        return center;
    }

    @Override
    public double getRadius(){
        return radius;
    }
    
    @Override
    public Color getColor(){
        return color;
    }
    
    @Override
    public void setColor(Color color){
        this.color = color;
    }
    
    @Override
    public String toString(){
        return (numberOfEdges + "-gon: center=" + center + ", radius=" + 
                radius + ", color=" + color);
    }
}
