package model.expresions;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.IType;
import model.types.RefType;
import model.value.IValue;
import model.value.RefValue;

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
