package org.example.tlcgui.model.expresions;

public enum LogicalOperator {
    AND,
    OR;

    @Override
    public String toString() {
        return switch (this) {
            case AND -> "&&";
            case OR -> "||";
        };
    }
}
