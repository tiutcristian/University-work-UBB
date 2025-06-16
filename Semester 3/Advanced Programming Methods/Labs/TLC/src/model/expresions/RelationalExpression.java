package model.expresions;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.BoolType;
import model.types.IType;
import model.types.IntType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;

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
