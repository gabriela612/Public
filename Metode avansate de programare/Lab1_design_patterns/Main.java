public class Main {
    public static void main(String[] args) {
        //System.out.println(NumarComplex.fromString("-3+i"));
//        ComplexExpression expr1 = new AddComplexExpression(new StartComplexExpression(new NumarComplex(1, 1)),
//                new StartComplexExpression(new NumarComplex(-2,-2)));
//        ComplexExpression expr2 = new SubComplexExpression(expr1, new StartComplexExpression(new NumarComplex(-6,-6)));
//        System.out.println(expr2.executeAllOperations());

        ExpressionParser expressionParser = new ExpressionParser();
        if (expressionParser.verify(args)) {
            ComplexExpression complexExpression = expressionParser.createExpression(args);
            System.out.println(complexExpression.executeAllOperations());
        }
    }
}
