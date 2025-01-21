package org.example.tlcgui.model.adt;

import org.example.tlcgui.model.value.IValue;

import java.util.HashMap;
import java.util.Map;

public class MyHeap implements MyIHeap {
    private HashMap<Integer, IValue> heap;
    private int nextFree;

    public MyHeap() {
        this.heap = new HashMap<>();
        this.nextFree = 1;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Integer key : heap.keySet()) {
            sb.append(key).append(" --> ").append(heap.get(key)).append("\n");
        }
        return sb.toString();
    }

    @Override
    public int allocate(IValue value) {
        heap.put(nextFree, value);
        return nextFree++;
    }

    @Override
    public IValue get(int address) {
        return heap.get(address);
    }

    @Override
    public boolean contains(int address) {
        return heap.containsKey(address);
    }

    @Override
    public void update(int address, IValue value) {
        heap.put(address, value);
    }

    @Override
    public void setContent(Map<Integer, IValue> newContent) {
        heap = (HashMap<Integer, IValue>) newContent;
    }

    @Override
    public Map<Integer, IValue> entrySet() {
        return heap;
    }
}
