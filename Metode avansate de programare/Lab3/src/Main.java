import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import domain.validators.ValidatorFactory;
import domain.validators.ValidatorStrategy;
import repository.InMemoryRepository;
import service.Service;
import ui.UI;

import java.sql.SQLException;

public class Main {

    public static void main(String[] args) throws SQLException {

        InMemoryRepository<Long, Utilizator> repoUtilizator = new
                InMemoryRepository<>(ValidatorFactory.getInstance().create(ValidatorStrategy.utilizator));

        InMemoryRepository<Tuple<Long, Long>, Prietenie>  repoPrietenie = new
                InMemoryRepository<>(ValidatorFactory.getInstance().create(ValidatorStrategy.prietenie));

        Service service = new Service(repoUtilizator, repoPrietenie);
        service.addUtilizator("U1FirstName", "U1LastName");
        service.addUtilizator("U2FirstName", "U2LastName");
        service.addUtilizator("U3FirstName", "U3LastName");
        service.addUtilizator("U4FirstName", "U4LastName");
        service.addUtilizator("U5FirstName", "U5LastName");
        service.addPrietenie(1l,2l);
        service.addPrietenie(3l, 4l);
        service.addPrietenie(4l, 5l);
        UI ui = new UI(service);
        ui.start();
        System.out.println("ok");
    }
}
