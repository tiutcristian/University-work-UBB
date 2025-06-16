package org.example.tlcgui.model.adt;

import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyBarrierTable implements MyIBarrierTable {
    private Map<Integer, Pair<Integer, List<Integer>>> barTable;

    public MyBarrierTable() {
        this.barTable = new HashMap<>();
    }

    @Override
    public void add(int index, Pair<Integer, List<Integer>> value) {
        this.barTable.put(index, value);
    }

    @Override
    public boolean contains(int foundIndex) {
        return this.barTable.containsKey(foundIndex);
    }

    @Override
    public Pair<Integer, List<Integer>> get(int foundIndex) {
        return this.barTable.get(foundIndex);
    }

    @Override
    public Map<Integer, Pair<Integer, List<Integer>>> getContent() {
        return this.barTable;
    }

    @Override
    public String toString() {
        return this.barTable.toString();
    }

}
