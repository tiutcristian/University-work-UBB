package org.example.tlcgui.model.adt;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.model.value.IValue;

import java.util.Map;

public interface MyIHeap {
    int allocate(IValue value);
    IValue get(int address) throws ADTException;
    boolean contains(int address);
    void update(int address, IValue value);
    void setContent(Map<Integer, IValue> newContent);
    Map<Integer, IValue> entrySet();
}
