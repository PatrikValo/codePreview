package cz.muni.fi.pb162.project.geometry;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.TreeSet;

/**
 *
 * @author Patrik Valo
 */
public final class LabeledPolygon extends SimplePolygon implements Labelable, Sortable, PolygonWritable{
    private static Gson gson = new GsonBuilder().setPrettyPrinting().create();
    /**
     *
     * @author Patrik Valo
     */
    public static class Builder implements Buildable<LabeledPolygon>, PolygonReadable{
        private Map<String, Vertex2D> map = new HashMap<>();
        
        /**
         * Prida oznacenie vrcholu a prislusny vrchol
         * @param label oznacenie
         * @param vert vrchol
         * @return Builder
         */
        public Builder addVertex(String label, Vertex2D vert) {
            if (label == null || vert == null) {
                throw new IllegalArgumentException("label or  vertex problem");
            }
            map.put(label, vert);
            return this;
        }
        
        @Override
        public LabeledPolygon build() {
            return new LabeledPolygon(map);
        }

        @Override
        public Builder read(InputStream is) throws IOException {
            Map<String, Vertex2D> tmp = new HashMap<>();
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            while(br.ready()) {
                String[] parts = br.readLine().split(" ", 3);
                if (parts.length != 3) {
                    throw new IOException("Paramters");
                }
                try {
                    double x = Double.valueOf(parts[0]);
                    double y = Double.valueOf(parts[1]);
                    tmp.put(parts[2], new Vertex2D(x, y));
                } catch(NumberFormatException ex) {
                    throw new IOException("Coordinate is not a number");
                }
            }
            map.putAll(tmp);
            return this;
        }

        @Override
        public Builder read(File file) throws IOException {
            try (FileInputStream fis = new FileInputStream(file)) {
                read(fis);
            }
            return this;
        }
        
    }
    
    private SortedMap<String, Vertex2D> vertices;
    
    private LabeledPolygon(Map<String, Vertex2D> vertices) {
        super(vertices.values().toArray(new Vertex2D[0]));
        this.vertices = new TreeMap<>(vertices);
    }

    @Override
    public Vertex2D getVertex(int index) {
        if (index < 0) {
            throw new IllegalArgumentException("Index");
        }
        List<Vertex2D> list = new ArrayList<>(vertices.values());
        return list.get(index % list.size());
    }

    @Override
    public int getNumVertices() {
        return vertices.size();
    }

    @Override
    public Vertex2D getVertex(String label) {
        Vertex2D vertex = vertices.get(label);
        if (vertex == null) {
            throw new IllegalArgumentException("vertex not exist");
        }
        return vertex;
    }

    @Override
    public Collection<String> getLabels() {
        return Collections.unmodifiableCollection(vertices.keySet());
    }

    @Override
    public Collection<String> getLabels(Vertex2D vertex) {
        List<String> list = new ArrayList<>();
        for (String key : vertices.keySet()) {
            if (vertices.get(key).equals(vertex)) {
                list.add(key);
            }
        }
        return list;
    }

    @Override
    public Collection<Vertex2D> getSortedVertices() {
        return new TreeSet<>(vertices.values());
    }

    @Override
    public Collection<Vertex2D> getSortedVertices(Comparator<Vertex2D> comparator) {
        TreeSet<Vertex2D> set = new TreeSet<>(comparator);
        set.addAll(vertices.values());
        return set;
    }
    
    /**
     * Najde duplicity vrcholov v mape
     * @return Collection vrcholov ktore boli v mape viackrat
     */
    public Collection<Vertex2D> duplicateVertices() {
        Set<Vertex2D> returnSet = new HashSet<>();
        Set<Vertex2D> set = new HashSet<>();
        
        for (Vertex2D vertex : vertices.values()) {
            if (!set.add(vertex)) {
                returnSet.add(vertex);
            }
        }
        return returnSet;        
    }
    
    @Override
    public void write(OutputStream os) throws IOException {
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(os));
        for(String key : vertices.keySet()) {
            Vertex2D vertex = vertices.get(key);
            bw.append(vertex.getX() + " " + vertex.getY() + " " + key);
            bw.newLine();
        }
        bw.flush();
    }

    @Override
    public void write(File file) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(file)) {
            write(fos);
        }
    }
    
    /**
     * Vypise mapu vo formate json
     * @param os OutputStream
     * @throws IOException exception
     */
    public void writeJson(OutputStream os) throws IOException {
        String jsonOutput = gson.toJson(vertices);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(os));
        bw.append(jsonOutput);
        bw.flush();
    } 
    
}
