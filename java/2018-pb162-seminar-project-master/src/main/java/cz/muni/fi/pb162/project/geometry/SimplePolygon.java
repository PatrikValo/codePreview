package cz.muni.fi.pb162.project.geometry;

import cz.muni.fi.pb162.project.exception.MissingVerticesException;
import cz.muni.fi.pb162.project.utils.SimpleMath;

/**
 *
 * @author Patrik Valo
 */
public abstract class SimplePolygon implements Polygon {
    /**
     * Constructor of SimplePolygon
     * @param vertices 
     */
    public SimplePolygon(Vertex2D[] vertices) {
        if (vertices == null) {
            throw new IllegalArgumentException("Array is null");
        }
        for (Vertex2D vertex : vertices) {
            if(vertex == null) {
                throw new IllegalArgumentException("Vertex is null");
            }
        }
        if (vertices.length < 3) {
            throw new MissingVerticesException("Number of vertices");
        }
    }
    @Override
    public abstract Vertex2D getVertex(int index);
    
    @Override
    public abstract int getNumVertices();
    
    @Override
    public double getHeight() {
        return SimpleMath.maxY(this) - SimpleMath.minY(this);
    }
    
    @Override
    public double getWidth() {
        return SimpleMath.maxX(this) - SimpleMath.minX(this);    
    }
    
    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("Polygon: ");
        str.append("vertices =");
        for (int i = 0; i < getNumVertices(); i++) {
            str.append(" ");
            str.append(getVertex(i).toString());
        }
        return str.toString();
    }
    
}
