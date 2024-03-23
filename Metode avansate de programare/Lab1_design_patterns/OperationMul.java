public class OperationMul implements Operation{

    @Override
    public NumarComplex apply(NumarComplex nr1, NumarComplex nr2) {
        return NumarComplex.inmultire(nr1, nr2);
    }
}
