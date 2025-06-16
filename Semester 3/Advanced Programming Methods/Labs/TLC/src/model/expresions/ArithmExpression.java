package model.expresions;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.IType;
import model.types.IntType;
import model.value.IValue;
import model.value.IntValue;

public class ArithmExpression implements IExpression {
    private final IExpression left;
    private final IExpression right;
    private final ArithmeticalOperator operator;

    public ArithmExpression(IExpression left, ArithmeticalOperator operator, IExpression right) {
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symTbl, MyIHeap heap)
            throws ADTException, ExpressionException {
        IValue value1 = left.eval(symTbl, heap);
        IValue value2 = right.eval(symTbl, heap);
        if (!value1.getType().equals(new IntType())) {
            throw new ExpressionException("First value is not int");
        }
        if (!value2.getType().equals(new IntType())) {
            throw new ExpressionException("Second value is not int");
        }

        IntValue int1 = (IntValue) value1;
        IntValue int2 = (IntValue) value2;

        switch (operator) {
            case ADD:
                return new IntValue(int1.getValue() + int2.getValue());
            case SUB:
                return new IntValue(int1.getValue() - int2.getValue());
            case MUL:
                return new IntValue(int1.getValue() * int2.getValue());
            case DIV:
            {
                if(int2.getValue() == 0)
                    throw new ExpressionException("Divide by zero");
                return new IntValue(int1.getValue() / int2.getValue());
            }
            default:
                throw new ExpressionException("Unknown operator");
        }
    }

    @Override
    public IExpression deepCopy() {
        return new ArithmExpression(left.deepCopy(), operator, right.deepCopy());
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException, KeyNotFoundException {
        IType typeLeft, typeRight;
        typeLeft = left.typecheck(typeEnv);
        typeRight = right.typecheck(typeEnv);
        if (typeLeft.equals(new IntType())) {
            if (typeRight.equals(new IntType())) {
                return new IntType();
            } else {
                throw new ExpressionException("Second operand is not an integer");
            }
        } else {
            throw new ExpressionException("First operand is not an integer");
        }
    }

    @Override
    public String toString() {
        return left.toString() + " " + operator + " " + right.toString();
    }
}
