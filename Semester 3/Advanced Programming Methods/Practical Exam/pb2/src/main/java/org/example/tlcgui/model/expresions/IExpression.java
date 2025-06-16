package org.example.tlcgui.model.expresions;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.model.adt.MyIHeap;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.adt.MyIDictionary;

public interface IExpression {
    IValue eval(MyIDictionary<String, IValue> symTbl, MyIHeap heap)
            throws ADTException, ExpressionException;
    IExpression deepCopy();
    IType typecheck(MyIDictionary<String,IType> typeEnv) throws ExpressionException, KeyNotFoundException;
}
