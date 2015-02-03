


private ExpressionTreeNode createExpressionTree(List<String> prefixExpression) {
    String element = prefixExpression.get(0);
    prefixExpression.remove(0);
    if (isNumeric(element)) {
        return new Leaf(Double.parseDouble(element));
    }
    ExpressionTreeNode left = createExpressionTree(prefixExpression);
    ExpressionTreeNode right = createExpressionTree(prefixExpression);
    return new ExpressionTreeNode(left, right, element);
}



