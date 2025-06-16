package org.example.tlcgui.model.expresions;


import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.adt.MyIHeap;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.value.IValue;

public class ValueExpression implements IExpression {

    private final IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symTbl, MyIHeap heap) {
        return value;
    }

    @Override
    public IExpression deepCopy() {
        return new ValueExpression(value.deepCopy());
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) {
        return value.getType();
    }

    public String toString(){
        return value.toString();
    }
}
