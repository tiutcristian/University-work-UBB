package org.example.tlcgui.model.adt;

import org.example.tlcgui.exceptions.KeyNotFoundException;

import java.util.Map;

public interface MyIDictionary <K, V>{
    void insert(K key, V value);
    V getValue(K key) throws KeyNotFoundException;
    void remove(K key) throws KeyNotFoundException;
    boolean contains(K key);
    Iterable<K> getKeys();
    Map<K, V> getContent();
    MyIDictionary<K, V> deepCopy();
}
