package org.example.tlcgui.model.value;

import org.example.tlcgui.model.types.IType;

public interface IValue {
    IType getType();
    IValue deepCopy();
    boolean equals(IValue other);
}
