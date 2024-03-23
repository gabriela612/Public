package domain.validators;

import domain.Utilizator;
import domain.validators.ValidationException;
import domain.validators.Validator;

public class UtilizatorValidator implements Validator<Utilizator> {
    private static UtilizatorValidator instance = null;
    private UtilizatorValidator() {}
    @Override
    public void validate(Utilizator entity) throws ValidationException {
        if (entity == null)
            throw new IsNullException("Utilizatorul este null");
        if (entity.getFirstName() == null || entity.getLastName() == null || entity.getId() == null) {
            throw new WrongDataException("Nu ati completat toate campurile");
        }
        if (!Character.isUpperCase(entity.getLastName().charAt(0)) || !Character.isUpperCase(entity.getFirstName().charAt(0))) {
            throw new WrongDataException("Numele trebuie sa inceapa cu litera mare.");
        }
        for (int i = 0; i < entity.getFullName().length(); i ++) {
            if (!Character.isLetterOrDigit(entity.getFullName().charAt(i)) && entity.getFullName().charAt(i) != ' ') {
                throw new WrongDataException("Numele trebuie sa contina doar litere sau numere");
            }
        }
        //TODO: implement method validate
    }

    public static UtilizatorValidator getInstance() {
        if (instance == null) {
            instance = new UtilizatorValidator();
        }
        return instance;
    }
}

