public class MulComplexExpression extends DecoratorComplexExpression{
    MulComplexExpression(ComplexExpression nr1, ComplexExpression nr2) {
        super(nr1, nr2);
    }

    @Override
    public NumarComplex executeAllOperations() {
        return NumarComplex.inmultire(nr1.executeAllOperations(), nr2.executeAllOperations());
    }
}
