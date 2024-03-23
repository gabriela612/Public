public class AddComplexExpression extends DecoratorComplexExpression{
    AddComplexExpression(ComplexExpression nr1, ComplexExpression nr2) {
        super(nr1, nr2);
    }

    @Override
    public NumarComplex executeAllOperations() {
        return NumarComplex.adunare(nr1.executeAllOperations(), nr2.executeAllOperations());
    }
}
