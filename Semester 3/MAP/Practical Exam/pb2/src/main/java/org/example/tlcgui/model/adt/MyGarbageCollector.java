package org.example.tlcgui.model.adt;

import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.RefValue;

import java.util.*;
import java.util.stream.Collectors;

public class MyGarbageCollector implements MyIGarbageCollector {

    @Override
    public List<Integer> getAddrFromAllSymTables(List<MyIDictionary<String, IValue>> symTables) {
        return symTables.stream()
                .map(MyIDictionary::getContent)
                .flatMap(m->m.values().stream())
                .filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddr();})
                .collect(Collectors.toList());
    }

    private List<Integer> getReachableAddresses(List<Integer> symTableAddr, Map<Integer, IValue> heap) {
        List<Integer> reachable = new ArrayList<>(symTableAddr);
        Queue<Integer> queue = new LinkedList<>(symTableAddr);

        while (!queue.isEmpty()) {
            int address = queue.poll();
            IValue value = heap.get(address);
            if (value instanceof RefValue) {
                int newAddress = ((RefValue) value).getAddr();
                if (!reachable.contains(newAddress)) {
                    reachable.add(newAddress);
                    queue.add(newAddress);
                }
            }
        }

        return reachable;
    }

    @Override
    public Map<Integer, IValue> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer, IValue> heap) {
        List<Integer> reachable = getReachableAddresses(symTableAddr, heap);
        return heap.entrySet().stream()
                .filter(e->reachable.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }
}
