package domain.validators;

import domain.Factory;

public class ValidatorFactory implements Factory<Validator, ValidatorStrategy> {
    private static ValidatorFactory instance = null;
    private ValidatorFactory() {}
    @Override
    public Validator create(ValidatorStrategy strategy) {
        if (strategy == ValidatorStrategy.utilizator) {
            UtilizatorValidator utilizatorValidator = UtilizatorValidator.getInstance();
            return utilizatorValidator;
        }
        if (strategy == ValidatorStrategy.prietenie) {
            PrietenieValidator prietenieValidator = PrietenieValidator.getInstance();
            return prietenieValidator;
        }
        return null;
    }
    public static ValidatorFactory getInstance() {
        if (instance == null) {
            instance = new ValidatorFactory();
        }
        return instance;
    }
}
