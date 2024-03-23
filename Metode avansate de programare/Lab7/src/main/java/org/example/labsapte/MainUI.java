package org.example.labsapte;

import org.example.domain.Prietenie;
import org.example.domain.Tuple;
import org.example.domain.Utilizator;
import org.example.repository.PrietenieBDRepository;
import org.example.repository.Repository;
import org.example.repository.UserDBRepository;
import org.example.service.Service;
import org.example.ui.UI;

public class MainUI {
    public static void main(String[] args) {
        String url="jdbc:postgresql://localhost:7777/SocialNetwork";
        String username = "postgres";
        String password = "MeyYaXrg";

        Repository<Long, Utilizator> userRepository =
                new UserDBRepository(url, username, password);
        Repository<Tuple<Long, Long>, Prietenie> prietenieRepository =
                new PrietenieBDRepository(url, username, password);

//        InMemoryRepository<Long, Utilizator> repoUtilizator = new
//                InMemoryRepository<>(ValidatorFactory.getInstance().create(ValidatorStrategy.utilizator));
//
//        InMemoryRepository<Tuple<Long, Long>, Prietenie>  repoPrietenie = new
//                InMemoryRepository<>(ValidatorFactory.getInstance().create(ValidatorStrategy.prietenie));

        Service service = new Service(userRepository, prietenieRepository, null);

        UI ui = new UI(service);
        ui.start();
        System.out.println("ok");
    }
}
