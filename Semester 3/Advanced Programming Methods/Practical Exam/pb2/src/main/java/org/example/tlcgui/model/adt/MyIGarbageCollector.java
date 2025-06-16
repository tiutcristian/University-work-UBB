package org.example.tlcgui.model.adt;

import org.example.tlcgui.model.value.IValue;

import java.util.List;
import java.util.Map;

public interface MyIGarbageCollector {
    Map<Integer,IValue> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer,IValue> heap);
    List<Integer> getAddrFromAllSymTables(List<MyIDictionary<String,IValue>> symTables);
}
