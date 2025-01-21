package org.example.tlcgui.model.value;

import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.IntType;

public class IntValue implements IValue{
    private final int value;

    public IntValue(int value) {
        this.value = value;
    }

    public int getValue(){
        return value;
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public IValue deepCopy() {
        return new IntValue(value);
    }

    @Override
    public boolean equals(IValue other) {
        return other instanceof IntValue && ((IntValue) other).value == this.value;
    }

    @Override
    public String toString(){
        return Integer.toString(value);
    }
}
