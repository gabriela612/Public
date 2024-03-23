abstract public class DecoratorComplexExpression implements ComplexExpression{
    protected ComplexExpression nr1;
    protected ComplexExpression nr2;
    DecoratorComplexExpression(ComplexExpression nr1, ComplexExpression nr2) {
        this.nr1 = nr1;
        this.nr2 = nr2;
    }
    @Override
    public abstract NumarComplex executeAllOperations();
}
