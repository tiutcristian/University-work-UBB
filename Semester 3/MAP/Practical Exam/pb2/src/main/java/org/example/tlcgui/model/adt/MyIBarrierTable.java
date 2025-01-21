package org.example.tlcgui.model.adt;

import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface MyIBarrierTable {

    void add(int index, Pair<Integer, List<Integer>> value);

    boolean contains(int foundIndex);

    Pair<Integer, List<Integer>> get(int foundIndex);

    Map<Integer, Pair<Integer, List<Integer>>> getContent();
}
