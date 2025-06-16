package org.example.tlcgui.model.value;

import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.RefType;

public class RefValue implements IValue {
    private int address;
    private IType locationType;

    public RefValue(int address, IType locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public int getAddr() {
        return address;
    }

    public IType getType() {
        return new RefType(locationType);
    }

    @Override
    public IValue deepCopy() {
        return new RefValue(address, locationType);
    }

    @Override
    public boolean equals(IValue other) {
        return other instanceof RefValue &&
                ((RefValue) other).address == this.address &&
                ((RefValue) other).locationType.equals(this.locationType);
    }

    @Override
    public String toString() {
        return "(" + address + ", " + locationType.toString() + ")";
    }
}