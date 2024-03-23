public class ComplexExpressionFactory implements  iComplexExpressionFactory{
    private ComplexExpressionFactory() {}
    static private ComplexExpressionFactory instance = null;
    static public ComplexExpressionFactory getInstance() {
        if (instance == null) {
            instance = new ComplexExpressionFactory();
        }
        return instance;
    }
    @Override
    public ComplexExpression create(ComplexExpression nr1, ComplexExpression nr2, Character operatie) {
        if (operatie.equals('+')) {
            return new AddComplexExpression(nr1, nr2);
        }
        if (operatie.equals('-')) {
            return new SubComplexExpression(nr1, nr2);
        }
        if (operatie.equals('*')) {
            return new MulComplexExpression(nr1, nr2);
        }
        if (operatie.equals('/')) {
            return new DivComplexExpression(nr1, nr2);
        }
        return null;
    }
}
