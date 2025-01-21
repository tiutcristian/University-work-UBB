package org.example.tlcgui.model.adt;
import org.example.tlcgui.exceptions.EmptyStackException;

public interface MyIStack <T>{
    public void push(T element);
    public T pop() throws EmptyStackException;
    public int size();
    public boolean isEmpty();
}
