package model.expresions;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.IType;
import model.value.IValue;

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
