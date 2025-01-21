package org.example.tlcgui.model.expresions;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.adt.MyIHeap;
import org.example.tlcgui.model.types.BoolType;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.IntType;
import org.example.tlcgui.model.value.BoolValue;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.IntValue;

public class RelationalExpression implements IExpression {
    private IExpression left;
    private IExpression right;
    private RelationalOperator operator;

    public RelationalExpression(IExpression left, RelationalOperator operator, IExpression right) {
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symTbl, MyIHeap heap)
            throws ADTException, ExpressionException {
        IValue leftValue = left.eval(symTbl, heap);
        if (!leftValue.getType().equals(new IntType())) {
            throw new ExpressionException("Left expression is not of type int");
        }

        IValue rightValue = right.eval(symTbl, heap);
        if (!rightValue.getType().equals(new IntType())) {
            throw new ExpressionException("Right expression is not of type int");
        }

        return new BoolValue(operator.apply(((IntValue)leftValue).getValue(), ((IntValue)rightValue).getValue()));
    }

    @Override
    public IExpression deepCopy() {
        return new RelationalExpression(left.deepCopy(), operator, right.deepCopy());
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException, KeyNotFoundException {
        IType typeLeft = left.typecheck(typeEnv);
        IType typeRight = right.typecheck(typeEnv);
        if (typeLeft.equals(new IntType())) {
            if (typeRight.equals(new IntType())) {
                return new BoolType();
            } else {
                throw new ExpressionException("Right expression is not of type int");
            }
        } else {
            throw new ExpressionException("Left expression is not of type int");
        }
    }

    @Override
    public String toString() {
        return left.toString() + " " + operator + " " + right.toString();
    }
}
