package model.value;

import model.types.BoolType;
import model.types.IType;

public class BoolValue implements IValue{
    private final boolean value;

    public BoolValue(boolean value) {
        this.value = value;
    }

    public boolean equals(IValue other){
        return other instanceof BoolValue && ((BoolValue)other).value == this.value;
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public IValue deepCopy() {
        return new BoolValue(this.value);
    }

    public boolean getValue(){
        return value;
    }

    @Override
    public String toString(){
        return String.valueOf(this.value);
    }
}
