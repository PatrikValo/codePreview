package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Patrik Valo
 */
public interface Colored {
    /**
     * Getter pre farbu
     * @return farba
     */
    Color getColor();
    
    /**
     * Nastavi farbu na pozadovanu farbu
     * @param color farba
     */
    void setColor(Color color);
}
