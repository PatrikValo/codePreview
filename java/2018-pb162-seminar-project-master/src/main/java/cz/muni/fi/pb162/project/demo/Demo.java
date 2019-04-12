package cz.muni.fi.pb162.project.demo;

import cz.muni.fi.pb162.project.geometry.LabeledPolygon;
import cz.muni.fi.pb162.project.geometry.Vertex2D;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;

/**
 * Class for running main method.
 *
 * @author Patrik Valo
 */
public class Demo {

    /**
     * 
     * @param args ignored
     * @throws IOException exception
     */
    public static void main(String[] args) throws IOException {
        File file = new File("polygon-ok.txt");
        LabeledPolygon polygon = new LabeledPolygon.Builder().read(file).
                addVertex("vrchol x", new Vertex2D(123, 456)).build();
        OutputStream os = System.out;
        polygon.writeJson(os);
        System.out.println("Hello World!");
    }
}
