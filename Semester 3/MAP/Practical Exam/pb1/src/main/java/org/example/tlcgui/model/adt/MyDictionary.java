package org.example.tlcgui.model.adt;

import org.example.tlcgui.exceptions.KeyNotFoundException;

import java.util.Map;
import java.util.HashMap;

public class MyDictionary<K, V> implements MyIDictionary<K, V>{
    private final Map<K, V> map;

    public MyDictionary() {
        this.map = new HashMap<>();
    }

    @Override
    public synchronized void insert(K key, V value) {
        this.map.put(key, value);
    }

    @Override
    public synchronized V getValue(K key) throws KeyNotFoundException {
        if (!this.map.containsKey(key)) {
            throw new KeyNotFoundException("Key doesn't exist");
        }
        return this.map.get(key);
    }

    @Override
    public synchronized void remove(K key) throws KeyNotFoundException {
        if (!this.map.containsKey(key)) {
            throw new KeyNotFoundException("Key doesn't exist");
        }
        this.map.remove(key);
    }

    @Override
    public synchronized boolean contains(K key) {
        return map.containsKey(key);
    }

    @Override
    public synchronized Iterable<K> getKeys() {
        return map.keySet();
    }

    @Override
    public synchronized Map<K, V> getContent() {
        return map;
    }

    @Override
    public synchronized MyIDictionary<K, V> deepCopy() {
        MyIDictionary<K, V> newDict = new MyDictionary<>();
        for (Map.Entry<K, V> entry : map.entrySet()) {
            newDict.insert(entry.getKey(), entry.getValue());
        }
        return newDict;
    }

    public synchronized Map<K, V> getMap() {
        return map;
    }

    @Override
    public synchronized String toString(){
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<K, V> entry : map.entrySet()) {
            sb.append(entry.getKey()).append("-->").append(entry.getValue()).append("\n");
        }
        return sb.toString();
    }
}
