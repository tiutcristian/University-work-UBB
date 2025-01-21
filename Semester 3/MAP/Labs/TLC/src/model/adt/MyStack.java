package model.adt;

import exceptions.EmptyStackException;

import java.util.Stack;

public class MyStack<T> implements MyIStack<T>{
    private Stack<T> stack;

    public MyStack()
    {
        this.stack = new Stack<>();
    }

    @Override
    public synchronized void push(T element) {
        this.stack.push(element);
    }

    @Override
    public synchronized T pop() throws EmptyStackException {
        if(this.stack.isEmpty())
            throw new EmptyStackException("Stack is empty");
        return this.stack.pop();
    }

    @Override
    public synchronized int size() {
        return this.stack.size();
    }

    @Override
    public synchronized boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public synchronized String toString(){
        StringBuilder sb = new StringBuilder();
        for(T element: this.stack){
            sb.append(element.toString()).append("\n");
        }
        return sb.toString();
    }
}
