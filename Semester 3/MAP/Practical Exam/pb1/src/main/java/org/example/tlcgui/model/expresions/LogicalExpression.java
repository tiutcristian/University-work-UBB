package org.example.tlcgui.model.expresions;


import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.adt.MyIHeap;
import org.example.tlcgui.model.types.BoolType;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.value.BoolValue;
import org.example.tlcgui.model.value.IValue;

public class LogicalExpression implements IExpression {
    private final IExpression left;
    private final IExpression right;
    private final LogicalOperator operator;

    public LogicalExpression(IExpression left, LogicalOperator operator, IExpression right) {
        this.left = left;
        this.operator = operator;
        this.right = right;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symTbl, MyIHeap heap)
            throws ADTException, ExpressionException {
        IValue evaluatedExpressionLeft = left.eval(symTbl, heap);
        IValue evaluatedExpressionRight = right.eval(symTbl, heap);
        if (!evaluatedExpressionLeft.getType().equals(new BoolType())) {
            throw new ExpressionException("Left expression is not of type BoolType");
        }
        if (!evaluatedExpressionRight.getType().equals(new BoolType())) {
            throw new ExpressionException("Right expression is not of type BoolType");
        }
        switch (operator) {
            case AND:
                return new BoolValue(((BoolValue) evaluatedExpressionLeft).getValue() &&
                        ((BoolValue) evaluatedExpressionRight).getValue());
            case OR:
                return new BoolValue(((BoolValue) evaluatedExpressionLeft).getValue() ||
                        ((BoolValue) evaluatedExpressionRight).getValue());
            default:
                throw new ExpressionException("Unknown operator");
        }
    }

    @Override
    public IExpression deepCopy() {
        return new LogicalExpression(left.deepCopy(), operator, right.deepCopy());
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException, KeyNotFoundException {
        IType typeLeft = left.typecheck(typeEnv);
        IType typeRight = right.typecheck(typeEnv);
        if (typeLeft.equals(new BoolType())) {
            if (typeRight.equals(new BoolType())) {
                return new BoolType();
            } else {
                throw new ExpressionException("Right expression is not of type BoolType");
            }
        } else {
            throw new ExpressionException("Left expression is not of type BoolType");
        }
    }

    @Override
    public String toString() {
        return left.toString() + " " + operator + " " + right.toString();
    }
}
