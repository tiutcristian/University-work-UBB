package model.types;


import model.value.IValue;
import model.value.RefValue;

public class RefType implements IType{
    private IType inner;

    public RefType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return inner;
    }

    @Override
    public String toString() {
        return "Ref(" + inner.toString() + ")";
    }

    @Override
    public boolean equals(IType obj) {
        if (obj instanceof RefType) {
            return inner.equals(((RefType) obj).getInner());
        } else {
            return false;
        }
    }

    @Override
    public IValue getDefaultValue() {
        return new RefValue(0, inner);
    }
}