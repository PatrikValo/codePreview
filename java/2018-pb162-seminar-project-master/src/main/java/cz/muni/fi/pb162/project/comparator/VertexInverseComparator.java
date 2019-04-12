package cz.muni.fi.pb162.project.comparator;

import cz.muni.fi.pb162.project.geometry.Vertex2D;
import java.util.Comparator;

/**
 *
 * @author Patrik Valo
 */
public class VertexInverseComparator implements Comparator<Vertex2D>{

    @Override
    public int compare(Vertex2D arg0, Vertex2D arg1) {
        return arg1.compareTo(arg0);
    }
    
}
