package cz.muni.fi.pb162.project.geometry;


import cz.muni.fi.pb162.project.utils.SimpleMath;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

/**
 *
 * @author Patrik Valo
 */
public class CollectionPolygon extends SimplePolygon{
    private final List<Vertex2D> vertices;
    
    /**
     * Constructor of CollectionPolygon
     * @param vertices Array
     */
    public CollectionPolygon(Vertex2D[] vertices){
        super(vertices);
        this.vertices = new ArrayList<>(Arrays.asList(vertices));   
    }
    
    /**
     * Constructor of CollenctionPolygon
     * @param vertices List
     */
    public CollectionPolygon(List<Vertex2D> vertices) {
        super(vertices.toArray(new Vertex2D[0]));
        this.vertices = new ArrayList<>(vertices);
    }
    
    @Override
    public Vertex2D getVertex(int index) {
        if (index < 0) {
            throw new IllegalArgumentException("index is less 0");
        }
        return vertices.get(index % vertices.size());
    }

    @Override
    public int getNumVertices() {
        return vertices.size();
    }
    
    /**
     * Remove the most left vertices
     * @return new CollectionPolygon
     */
    public CollectionPolygon withoutLeftmostVertices() {
        if (getNumVertices() == 0) {
            throw new IllegalArgumentException("empty"); 
        }
        
        double min = SimpleMath.minX(this);
        List<Vertex2D> list = new ArrayList<>(vertices);
        Iterator<Vertex2D> iterator = list.iterator();
        
        while(iterator.hasNext()) {
            Vertex2D vertex = iterator.next();
            if(min == vertex.getX()) {
                iterator.remove();
            }
        }
        return new CollectionPolygon(list);
    }
    
    @Override
    public boolean equals(Object o) {
        if (o == null || o.getClass() != getClass()) return false;
        CollectionPolygon collectionPolygon = (CollectionPolygon) o;
        if (collectionPolygon.getNumVertices() != getNumVertices()) return false;
        for (int i = 0; i < getNumVertices(); i++) {
            if (!vertices.get(i).equals(collectionPolygon.getVertex(i))){
                return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 47 * hash + Objects.hashCode(this.vertices);
        return hash;
    }
    
}
