public class OperationSub implements Operation {
    @Override
    public NumarComplex apply(NumarComplex nr1, NumarComplex nr2) {
        return NumarComplex.scadere(nr1, nr2);
    }
}
