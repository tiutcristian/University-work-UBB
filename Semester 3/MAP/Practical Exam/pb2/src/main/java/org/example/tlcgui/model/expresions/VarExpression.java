package org.example.tlcgui.model.expresions;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.adt.MyIHeap;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.value.IValue;

public class VarExpression implements IExpression {

    private final String variable;

    public VarExpression(String variable) {
        this.variable = variable;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symTbl, MyIHeap heap) throws ADTException {
        return symTbl.getValue(variable);
    }

    @Override
    public IExpression deepCopy() {
        return new VarExpression(variable);
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException {
        return typeEnv.getValue(variable);
    }

    public String toString(){
        return variable;
    }
}
