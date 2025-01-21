package org.example.tlcgui.model.types;

import org.example.tlcgui.model.value.IValue;

public interface IType {
    boolean equals(IType obj);
    IValue getDefaultValue();
}
