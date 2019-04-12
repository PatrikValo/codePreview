package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Patrik Valo
 */
public class RegularOctagon extends GeneralRegularPolygon{
    /**
     * Konstruktor RegularOctagon
     * @param center stred
     * @param radius polomer
     */
    public RegularOctagon(Vertex2D center, double radius){
        super(center, 8, radius);
    }
    
}
