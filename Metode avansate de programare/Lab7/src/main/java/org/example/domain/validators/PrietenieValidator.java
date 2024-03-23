package org.example.domain.validators;

import org.example.domain.Prietenie;

public class PrietenieValidator implements Validator<Prietenie> {
    private static PrietenieValidator instance = null;
    private PrietenieValidator() {}
    @Override
    public void validate(Prietenie entity) throws ValidationException {
        if (entity == null)
            throw new org.example.domain.validators.IsNullException("Prietenia nu trebuie sa fie null");
        if (entity.getId() == null || entity.getId().getLeft() == null || entity.getId().getRight() == null)
            throw new org.example.domain.validators.IsNullException("Id-ul prieteniei nu trebuie sa fie null");
        if (entity.getId().getLeft().equals(entity.getId().getRight())) {
            throw new WrongDataException("Un utilizator nu se poate imprietenii cu el insusi.");
        }
    }

    public static PrietenieValidator getInstance() {
        if (instance == null) {
            instance = new PrietenieValidator();
        }
        return instance;
    }
}
