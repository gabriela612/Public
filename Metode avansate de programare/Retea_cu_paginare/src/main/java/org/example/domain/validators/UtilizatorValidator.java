package org.example.domain.validators;

import org.example.domain.Utilizator;
import org.example.domain.validators.ValidationException;
import org.example.domain.validators.Validator;

public class UtilizatorValidator implements Validator<Utilizator> {
    private static UtilizatorValidator instance = null;

    public static boolean validareNumeUtilizator(String firstName, String lastName) {
        if (!Character.isUpperCase(lastName.charAt(0)) || !Character.isUpperCase(firstName.charAt(0))) {
            return false;
        }
        String fullName = firstName + " " + lastName;
        for (int i = 0; i < fullName.length(); i ++) {
            if (!Character.isLetterOrDigit(fullName.charAt(i)) && fullName.charAt(i) != ' ') {
                return false;
            }
        }
        return true;
    }
    private UtilizatorValidator() {

    }
    @Override
    public void validate(Utilizator entity) throws ValidationException {
        if (entity == null)
            throw new IsNullException("Utilizatorul este null");
        if (entity.getFirstName() == null || entity.getLastName() == null) {
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

