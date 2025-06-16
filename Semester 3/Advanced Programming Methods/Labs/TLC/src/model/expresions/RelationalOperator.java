package model.expresions;

public enum RelationalOperator {
    EQUALS,
    NOT_EQUALS,
    LESS,
    LESS_OR_EQUALS,
    GREATER,
    GREATER_OR_EQUALS;

    @Override
    public String toString() {
        return switch (this) {
            case EQUALS -> "==";
            case NOT_EQUALS -> "!=";
            case LESS -> "<";
            case LESS_OR_EQUALS -> "<=";
            case GREATER -> ">";
            case GREATER_OR_EQUALS -> ">=";
        };
    }

    public boolean apply(int left, int right) {
        return switch (this) {
            case EQUALS -> left == right;
            case NOT_EQUALS -> left != right;
            case LESS -> left < right;
            case LESS_OR_EQUALS -> left <= right;
            case GREATER -> left > right;
            case GREATER_OR_EQUALS -> left >= right;
        };
    }
}
