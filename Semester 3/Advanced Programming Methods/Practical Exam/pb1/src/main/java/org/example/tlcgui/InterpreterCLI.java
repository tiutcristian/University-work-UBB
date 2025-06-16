package org.example.tlcgui;

import org.example.tlcgui.model.expresions.*;
import org.example.tlcgui.model.statements.*;
import org.example.tlcgui.model.types.BoolType;
import org.example.tlcgui.model.types.IntType;
import org.example.tlcgui.model.types.RefType;
import org.example.tlcgui.model.value.BoolValue;
import org.example.tlcgui.model.value.IntValue;
import org.example.tlcgui.view.TextMenu;

import java.util.ArrayList;
import java.util.List;

public class InterpreterCLI {
    private static void startTextMenu(List<IStatement> programs) {
        new TextMenu(programs).show();
    }

    public static List<IStatement> basicExamples() {
        List<IStatement> programs = new ArrayList<>();
        programs.add(
                new CompStatement(
                        new VarDeclStatement("v", new IntType()),
                        new CompStatement(
                                new AssignStatement("v",
                                        new ValueExpression(new IntValue(2))
                                ),
                                new PrintStatement(new VarExpression("v"))
                        )
                )
        );
        programs.add(
                new CompStatement(
                        new VarDeclStatement("a", new IntType()),
                        new CompStatement(
                                new VarDeclStatement("b", new IntType()),
                                new CompStatement(
                                        new AssignStatement("a",
                                                new ArithmExpression(
                                                        new ValueExpression(new IntValue(2)),
                                                        ArithmeticalOperator.ADD,
                                                        new ArithmExpression(
                                                                new ValueExpression(new IntValue(3)),
                                                                ArithmeticalOperator.MUL,
                                                                new ValueExpression(new IntValue(5))
                                                        )
                                                )
                                        ),
                                        new CompStatement(
                                                new AssignStatement("b",
                                                        new ArithmExpression(
                                                                new VarExpression("a"),
                                                                ArithmeticalOperator.ADD,
                                                                new ValueExpression(new IntValue(1))
                                                        )
                                                ),
                                                new PrintStatement(new VarExpression("b"))
                                        )
                                )
                        )
                )
        );
        programs.add(
                new CompStatement(
                        new VarDeclStatement("a",new BoolType()),
                        new CompStatement(
                                new VarDeclStatement("v", new IntType()),
                                new CompStatement(
                                        new AssignStatement("a",
                                                new ValueExpression(new BoolValue(true))
                                        ),
                                        new CompStatement(
                                                new IfStatement(
                                                        new VarExpression("a"),
                                                        new AssignStatement("v",
                                                                new ValueExpression(new IntValue(2))
                                                        ),
                                                        new AssignStatement("v",
                                                                new ValueExpression(new IntValue(3))
                                                        )
                                                ),
                                                new PrintStatement(new VarExpression("v"))
                                        )
                                )
                        )
                )
        );
        return programs;
    }

    public static List<IStatement> dynamicAllocationExamples() {
        List<IStatement> programs = new ArrayList<>();
        programs.add( // Heap alloc example:  Ref int v;new(v,20);Ref Ref int a;new(a,v);print(v);print(a)
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new CompStatement(
                                new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                        new CompStatement(
                                                new HeapAllocStatement("a", new VarExpression("v")),
                                                new CompStatement(
                                                        new PrintStatement(new VarExpression("v")),
                                                        new PrintStatement(new VarExpression("a"))
                                                )
                                        )
                                )
                        )
                )
        );
        programs.add( // Heap read example:  Ref int v;new(v,20);Ref Ref int a;new(a,v);print(rH(v));print(rH(rH(a))+5)
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new CompStatement(
                                new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                        new CompStatement(
                                                new HeapAllocStatement("a", new VarExpression("v")),
                                                new CompStatement(
                                                        new PrintStatement(new HeapReadExpression(new VarExpression("v"))),
                                                        new PrintStatement(
                                                                new ArithmExpression(
                                                                        new HeapReadExpression(new HeapReadExpression(new VarExpression("a"))),
                                                                        ArithmeticalOperator.ADD,
                                                                        new ValueExpression(new IntValue(5))
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        programs.add(  // Heap write example:  Ref int v;new(v,20);print(rH(v));wH(v,30);print(rH(v)+5);
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new CompStatement(
                                new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new PrintStatement(new HeapReadExpression(new VarExpression("v"))),
                                        new CompStatement(
                                                new HeapWriteStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(
                                                        new ArithmExpression(
                                                                new HeapReadExpression(new VarExpression("v")),
                                                                ArithmeticalOperator.ADD,
                                                                new ValueExpression(new IntValue(5))
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        programs.add( // Garbage collector example:  Ref int v;new(v,20);Ref Ref int a;new(a,v);new(v,30);print(rH(rH(a)))
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new CompStatement(
                                new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                        new CompStatement(
                                                new HeapAllocStatement("a", new VarExpression("v")),
                                                new CompStatement(
                                                        new HeapAllocStatement("v", new ValueExpression(new IntValue(30))),
                                                        new PrintStatement(new HeapReadExpression(new HeapReadExpression(new VarExpression("a"))))
                                                )
                                        )
                                )
                        )
                )
        );
        programs.add( // Garbage collector example:  Ref int v;new(v,20);new(v,30);print(rH(v))
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new CompStatement(
                                new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new HeapAllocStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new HeapReadExpression(new VarExpression("v")))
                                )
                        )
                )
        );
        return programs;
    }

    public static List<IStatement> whileExample() {
        List<IStatement> programs = new ArrayList<>();
        programs.add(  // int v; v=4; (while (v>0) print(v);v=v-1);print(v)
                new CompStatement(
                        new VarDeclStatement("v", new IntType()),
                        new CompStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(4))),
                                new CompStatement(
                                        new WhileStatement(
                                                new RelationalExpression(
                                                        new VarExpression("v"),
                                                        RelationalOperator.GREATER,
                                                        new ValueExpression(new IntValue(0))
                                                ),
                                                new CompStatement(
                                                        new PrintStatement(new VarExpression("v")),
                                                        new AssignStatement("v",
                                                                new ArithmExpression(
                                                                        new VarExpression("v"),
                                                                        ArithmeticalOperator.SUB,
                                                                        new ValueExpression(new IntValue(1))
                                                                )
                                                        )
                                                )
                                        ),
                                        new PrintStatement(new VarExpression("v"))
                                )
                        )
                )
        );
        return programs;
    }

    public static List<IStatement> forkExample() {
        List<IStatement> programs = new ArrayList<>();
        programs.add(
            //int v; Ref int a; v=10;new(a,22);
            //fork(wH(a,30);v=32;print(v);print(rH(a)));
            //print(v);print(rH(a))
            new CompStatement(
                new VarDeclStatement("v", new IntType()),
                new CompStatement(
                    new VarDeclStatement("a", new RefType(new IntType())),
                    new CompStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(10))),
                        new CompStatement(
                            new HeapAllocStatement("a", new ValueExpression(new IntValue(22))),
                            new CompStatement(
                                new ForkStatement(
                                    new CompStatement(
                                        new HeapWriteStatement("a", new ValueExpression(new IntValue(30))),
                                        new CompStatement(
                                            new AssignStatement("v", new ValueExpression(new IntValue(32))),
                                            new CompStatement(
                                                new PrintStatement(new VarExpression("v")),
                                                new PrintStatement(new HeapReadExpression(new VarExpression("a")))
                                            )
                                        )
                                    )
                                ),
                                new CompStatement(
                                    new PrintStatement(new VarExpression("v")),
                                    new PrintStatement(new HeapReadExpression(new VarExpression("a")))
                                )
                            )
                        )
                    )
                )
            )
        );
        programs.add(
                // Ref int a;new(a,20);fork(Ref int b;new(b,30);print(rH(a));print(rH(b)))
                new CompStatement(
                        new VarDeclStatement("a", new RefType(new IntType())),
                        new CompStatement(
                                new HeapAllocStatement("a", new ValueExpression(new IntValue(20))),
                                new ForkStatement(
                                        new CompStatement(
                                                new VarDeclStatement("b", new RefType(new IntType())),
                                                new CompStatement(
                                                        new HeapAllocStatement("b", new ValueExpression(new IntValue(30))),
                                                        new CompStatement(
                                                                new PrintStatement(new HeapReadExpression(new VarExpression("a"))),
                                                                new PrintStatement(new HeapReadExpression(new VarExpression("b")))
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        return programs;
    }

    public static List<IStatement> typeCheckerFailingExample() {
        List<IStatement> programs = new ArrayList<>();
        programs.add( // Ref int v; v=10
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new AssignStatement("v", new ValueExpression(new IntValue(10)))
                )
        );
        return programs;
    }

    public static List<IStatement> repUntilExample() {
        List<IStatement> programs = new ArrayList<>();
        // int v; int x; int y; v=0;
        //(repeat (fork(print(v);v=v-1);v=v+1) until v==3);
        //x=1;nop;y=3;nop;
        //print(v*10)
        programs.add( // Ref int v; v=10
            new CompStatement(
                new VarDeclStatement("v", new IntType()),
                new CompStatement(
                    new VarDeclStatement("x", new IntType()),
                    new CompStatement(
                        new VarDeclStatement("y", new IntType()),
                        new CompStatement(
                            new AssignStatement("v", new ValueExpression(new IntValue(0))),
                            new CompStatement(
                                new RepUntilStatement(
                                    new CompStatement(
                                        new ForkStatement(
                                            new CompStatement(
                                                new PrintStatement(new VarExpression("v")),
                                                new AssignStatement("v",
                                                    new ArithmExpression(
                                                        new VarExpression("v"),
                                                        ArithmeticalOperator.SUB,
                                                        new ValueExpression(new IntValue(1))
                                                    )
                                                )
                                            )
                                        ),
                                        new AssignStatement("v",
                                            new ArithmExpression(
                                                new VarExpression("v"),
                                                ArithmeticalOperator.ADD,
                                                new ValueExpression(new IntValue(1))
                                            )
                                        )
                                    ),
                                    new RelationalExpression(
                                        new VarExpression("v"),
                                        RelationalOperator.EQUALS,
                                        new ValueExpression(new IntValue(3))
                                    )
                                ),
                                new CompStatement(
                                    new AssignStatement("x", new ValueExpression(new IntValue(1))),
                                    new CompStatement(
                                        new NopStatement(),
                                        new CompStatement(
                                            new AssignStatement("y", new ValueExpression(new IntValue(3))),
                                            new CompStatement(
                                                new NopStatement(),
                                                new PrintStatement(
                                                    new ArithmExpression(
                                                        new VarExpression("v"),
                                                        ArithmeticalOperator.MUL,
                                                        new ValueExpression(new IntValue(10))
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        );
        return programs;
    }

    public static void main(String[] args) {
//        startTextMenu(basicExamples());
//        startTextMenu(dynamicAllocationExamples());
//        startTextMenu(whileExample());
//        startTextMenu(forkExample());
//        startTextMenu(typeCheckerFailingExample());
        startTextMenu(repUntilExample());
    }
}