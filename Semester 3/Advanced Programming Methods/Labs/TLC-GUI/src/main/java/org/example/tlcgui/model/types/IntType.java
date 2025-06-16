package org.example.tlcgui.model.types;

import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.IntValue;

public class IntType implements IType{

    @Override
    public boolean equals(IType obj) {
        return obj instanceof IntType;
    }

    @Override
    public IValue getDefaultValue() {
        return new IntValue(0);
    }

    public String toString(){
        return "int";
    }
}
