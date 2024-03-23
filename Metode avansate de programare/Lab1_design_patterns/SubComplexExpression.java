public class SubComplexExpression extends DecoratorComplexExpression{
    SubComplexExpression(ComplexExpression nr1, ComplexExpression nr2) {
        super(nr1, nr2);
    }

    @Override
    public NumarComplex executeAllOperations() {
        return NumarComplex.scadere(nr1.executeAllOperations(), nr2.executeAllOperations());
    }
}
