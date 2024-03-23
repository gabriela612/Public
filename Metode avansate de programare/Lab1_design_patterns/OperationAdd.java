public class OperationAdd implements Operation{
    @Override
    public NumarComplex apply(NumarComplex nr1, NumarComplex nr2) {

        return NumarComplex.adunare(nr1, nr2);
    }
}
