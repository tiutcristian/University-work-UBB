package org.example.tlcgui.model.expresions;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.adt.MyIHeap;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.RefType;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.RefValue;

public class HeapReadExpression implements IExpression {
    private IExpression expression;

    public HeapReadExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symTbl, MyIHeap heap)
            throws ADTException, ExpressionException {
        IValue evalExpr = expression.eval(symTbl, heap);
        if (!(evalExpr.getType() instanceof RefType)) {
            throw new ExpressionException("Expression must be RefType");
        }

        int addr = ((RefValue)evalExpr).getAddr();
        if (!heap.contains(addr)) {
            throw new ExpressionException("Address not in heap");
        }

        return heap.get(addr);
    }

    @Override
    public IExpression deepCopy() {
        return new HeapReadExpression(expression.deepCopy());
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException, KeyNotFoundException {
        IType expType = expression.typecheck(typeEnv);
        if (expType instanceof RefType reft) {
            return reft.getInner();
        } else {
            throw new ExpressionException("The HeapRead argument is not a RefType");
        }
    }

    @Override
    public String toString() {
        return "readHeap(" + expression.toString() + ")";
    }
}
