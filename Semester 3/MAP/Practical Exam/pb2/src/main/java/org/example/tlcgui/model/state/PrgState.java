package org.example.tlcgui.model.state;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.EmptyStackException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.*;
import org.example.tlcgui.model.statements.IStatement;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class PrgState {
    private MyIDictionary<String, IValue> symTable;
    private MyIStack<IStatement> exeStack;
    private MyIList<String> output;
    private MyIDictionary <StringValue, BufferedReader> fileTable;
    private MyIHeap heap;
    private MyIBarrierTable barrierTable;

    private int id;
    private static int lastId = 0;

    private synchronized int getNewId(){
        lastId++;
        return lastId;
    }

    public PrgState(
            MyIDictionary<String, IValue> symTable,
            MyIStack<IStatement> exeStack,
            MyIList<String> output,
            MyIDictionary<StringValue, BufferedReader> fileTable,
            MyIHeap heap,
            MyIBarrierTable barrierTable,
            IStatement initialState
    ) {
        this.symTable = symTable;
        this.exeStack = exeStack;
        this.exeStack.push(initialState);
        this.output = output;
        this.fileTable = fileTable;
        this.heap = heap;
        this.barrierTable = barrierTable;
        this.id = getNewId();
    }

    public MyIDictionary<String, IValue> getSymTable() {
        return symTable;
    }

    public MyIStack<IStatement> getExeStack() {
        return exeStack;
    }

    public MyIList<String> getOutput() {
        return output;
    }

    public MyIDictionary<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public MyIHeap getHeap() {
        return heap;
    }

    public String toString(){
        return "\t\tProgram State of ID: " + this.id + "\n" +
                "ExeStack:\n" + this.exeStack.toString() + "\n" +
                "SymTable:\n" + this.symTable.toString() + "\n" +
                "Output:\n" + this.output.toString() + "\n" +
                "FileTable:\n" + this.fileTable.toString() + "\n" +
                "Heap:\n" + this.heap.toString() + "\n" +
                "BarrierTable:\n" + this.barrierTable.toString() + "\n" +
                "========================================\n";
    }

    public Boolean isNotCompleted(){
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStep() throws ADTException, StatementException, IOException, ExpressionException {
        if(exeStack.isEmpty()) {
            throw new EmptyStackException("Execution stack is empty");
        }
        IStatement crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }

    public int getId() {
        return id;
    }

    public MyIBarrierTable getBarrierTable() {
        return barrierTable;
    }
}
