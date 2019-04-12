package cz.muni.fi.pb162.project.geometry;

import java.util.Arrays;

/**
 *
 * @author Patrik Valo
 */
public class ArrayPolygon extends SimplePolygon{
    private Vertex2D[] arrayOfVertex; 
    
    /**
     * Konstruktor ArrayPolygon
     * @param array vstupne pole
     * ak pole obsahuje null alebo je null vyhodi vynimku, inak sa
     * prekopiruje
     */
    public ArrayPolygon(Vertex2D[] array){
        super(array);
        this.arrayOfVertex = Arrays.copyOf(array, array.length);
        
    }  

    @Override
    public Vertex2D getVertex(int index) {
        if (index < 0) {
            throw new IllegalArgumentException("index is less 0");
        }
        return arrayOfVertex[index % getNumVertices()];
    }

    @Override
    public int getNumVertices() {
        return arrayOfVertex.length;
    }
    
    @Override
    public boolean equals(Object o) {
        if (o == null || o.getClass() != getClass()) return false;
        ArrayPolygon arrayPolygon = (ArrayPolygon) o;
        if (arrayPolygon.getNumVertices() != getNumVertices()) return false;
        for (int i = 0; i < getNumVertices(); i++) {
            if (!arrayOfVertex[i].equals(arrayPolygon.getVertex(i))){
                return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 89 * hash + Arrays.deepHashCode(this.arrayOfVertex);
        return hash;
    }
}
