public class OperationDiv implements Operation{

    @Override
    public NumarComplex apply(NumarComplex nr1, NumarComplex nr2) {
        return NumarComplex.impartire(nr1, nr2);
    }
}
