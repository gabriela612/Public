public class DivComplexExpression extends DecoratorComplexExpression{
    DivComplexExpression(ComplexExpression nr1, ComplexExpression nr2) {
        super(nr1, nr2);
    }

    @Override
    public NumarComplex executeAllOperations() {
        return NumarComplex.impartire(nr1.executeAllOperations(), nr2.executeAllOperations());
    }
}
