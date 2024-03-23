public class StartComplexExpression implements ComplexExpression {
    NumarComplex nr;
    StartComplexExpression(NumarComplex nr)
    {
        this.nr = nr;
    }
    @Override
    public NumarComplex executeAllOperations() {
        return nr;
    }
}
