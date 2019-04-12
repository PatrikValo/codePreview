package cz.muni.fi.pb162.project.geometry;

import cz.muni.fi.pb162.project.exception.EmptyDrawableException;
import cz.muni.fi.pb162.project.exception.MissingVerticesException;
import cz.muni.fi.pb162.project.exception.TransparentColorException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 *
 * @author Patrik Valo
 */
public class Paper implements Drawable, PolygonFactory{
    private Set<ColoredPolygon> polygons;
    private Color color = Color.BLACK;
    
    /**
     * Constructor of Paper
     */
    public Paper() {
        this.polygons = new HashSet<>();
    }
    
    /**
     * Constructor of Paper
     * @param drawable drawable
     */
    public Paper(Drawable drawable) {
        this.polygons = new HashSet<>(drawable.getAllDrawnPolygons());
    }
    @Override
    public void changeColor(Color color) {
        this.color = color;
    }

    @Override
    public void drawPolygon(Polygon polygon) throws TransparentColorException {
        if (color != Color.WHITE) {
            polygons.add(new ColoredPolygon(polygon, color));
        } else {
            throw new TransparentColorException("Darwing with white color");
        }
    }

    @Override
    public void erasePolygon(ColoredPolygon polygon) {
        polygons.remove(polygon);
    }

    @Override
    public void eraseAll() throws EmptyDrawableException {
        if (polygons.isEmpty()) {
            throw new EmptyDrawableException("Empty paper");
        }
        polygons.removeAll(polygons);
    }

    @Override
    public Collection<ColoredPolygon> getAllDrawnPolygons() {
        return Collections.unmodifiableSet(polygons);
    }

    @Override
    public int uniqueVerticesAmount() {
        Set<Vertex2D> set = new HashSet<>();
        for (ColoredPolygon polygon : polygons) {
            for (int i = 0; i < polygon.getPolygon().getNumVertices(); ++i) {
                set.add(polygon.getPolygon().getVertex(i));
            }
        }
        return set.size();
    }

    @Override
    public Polygon tryToCreatePolygon(List<Vertex2D> vertices) throws MissingVerticesException {
        if (vertices == null) {
            throw new NullPointerException("Null list");
        }
        List<Vertex2D> copyVertices = new ArrayList<>(vertices);
        try {
            return new CollectionPolygon(copyVertices);
        } catch (IllegalArgumentException e){
            copyVertices.removeAll(Collections.singletonList(null));
            return new CollectionPolygon(copyVertices);         
        }      
    }

    @Override
    public void tryToDrawPolygons(List<List<Vertex2D>> collectionPolygons) throws EmptyDrawableException {
        Iterator<List<Vertex2D>> iterator = collectionPolygons.iterator();
        Throwable cause = null;
        while(iterator.hasNext()) {
            List<Vertex2D> list = iterator.next();
            try {
                Polygon polygon = tryToCreatePolygon(list);
                drawPolygon(polygon);
            } catch (TransparentColorException e) {
                color = Color.BLACK;
                cause = e;
            } catch (MissingVerticesException | NullPointerException e) {
                cause = e;
            }
        }
        if (polygons.isEmpty()) {
            throw new EmptyDrawableException("Empty paper", cause);
        }
    }
    
    /**
     * Return polygons, which has color same as color
     * @param color color
     * @return Collection contain Polygon with color
     */
    public Collection<Polygon> getPolygonsWithColor(Color color) {
        Set<Polygon> set = new HashSet<>();
        for (ColoredPolygon polygon : polygons) {
            if (polygon.getColor() == color) {
                set.add(polygon.getPolygon());
            }
        }
        return set;
    }
}
