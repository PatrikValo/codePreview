package cz.muni.fi.pb162.project.geometry;

import java.util.Objects;

/**
 *
 * @author Patrik Valo
 */
public class ColoredPolygon {
    private final Polygon polygon;
    private final Color color;
    
    /**
     * COnstructor of ColoredPolygon
     * @param polygon polygon
     * @param color color
     */
    public ColoredPolygon(Polygon polygon, Color color) {
        this.polygon = polygon;
        this.color = color;
    }
    
    public Polygon getPolygon() {
        return polygon;
    }
    
    public Color getColor() {
        return color;
    }
    
    @Override
    public boolean equals(Object o) {
        if (o == null || o.getClass() != getClass()) return false;
        ColoredPolygon coloredPolygon = (ColoredPolygon) o;
        return polygon.equals(coloredPolygon.getPolygon()) && 
                color.equals(coloredPolygon.getColor());
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 97 * hash + Objects.hashCode(this.polygon);
        hash = 97 * hash + Objects.hashCode(this.color);
        return hash;
    }
    
    
    
}
