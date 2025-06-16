package org.example.tlcgui.model.value;

import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.StringType;

public class StringValue implements IValue {
    String value;

    public StringValue(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public IValue deepCopy() {
        return new StringValue(value);
    }

    @Override
    public boolean equals(IValue other) {
        return other instanceof StringValue &&
                this.value.equals(((StringValue) other).value);
    }

    @Override
    public String toString() {
        return "\"" + value + "\"";
    }
}
