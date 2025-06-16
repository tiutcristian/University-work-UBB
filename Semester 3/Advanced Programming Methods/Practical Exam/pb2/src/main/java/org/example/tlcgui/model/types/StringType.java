package org.example.tlcgui.model.types;

import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.StringValue;

public class StringType implements IType {

    @Override
    public boolean equals(IType obj) {
        return obj instanceof StringType;
    }

    @Override
    public IValue getDefaultValue() {
        return new StringValue("");
    }

    @Override
    public String toString() {
        return "string";
    }
}
