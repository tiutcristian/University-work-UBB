package org.example.tlcgui.model.types;

import org.example.tlcgui.model.value.BoolValue;
import org.example.tlcgui.model.value.IValue;

public class BoolType implements IType{

    @Override
    public boolean equals(IType obj) {
        return obj instanceof BoolType;
    }

    @Override
    public IValue getDefaultValue() {
        return new BoolValue(false);
    }

    public String toString() {
        return "bool";
    }
}
