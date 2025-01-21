package model.value;

import model.types.IType;
import model.types.StringType;

public class StringValue implements IValue {
    String value;

    public StringValue(String value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public IValue deepCopy() {
        return new StringValue(value);
    }

    public boolean equals(IValue other) {
        return other instanceof StringValue && this.value.equals(((StringValue) other).value);
    }

    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "\"" + value + "\"";
    }
}
