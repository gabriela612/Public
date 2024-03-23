package org.example.labsapte;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.scene.paint.Paint;
import javafx.stage.Stage;
import org.example.domain.Mesaj;
import org.example.domain.Prietenie;
import org.example.domain.Tuple;
import org.example.domain.Utilizator;
import org.example.repository.MesajDBRepository;
import org.example.repository.PrietenieBDRepository;
import org.example.repository.Repository;
import org.example.repository.UserDBRepository;
import org.example.repository.paging.Pageable;
import org.example.service.Service;

import java.awt.*;
import java.io.IOException;
import java.sql.SQLException;

public class UsersApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {

        String url="jdbc:postgresql://localhost:7777/SocialNetwork";
        String username = "postgres";
        String password = "MeyYaXrg";

        Repository<Tuple<Long, Long>, Mesaj> mesajRepository =
                new MesajDBRepository(url, username, password);
        UserDBRepository userRepository =
                new UserDBRepository(url, username, password);
        Repository<Tuple<Long, Long>, Prietenie> prietenieRepository =
                new PrietenieBDRepository(url, username, password);

        Service service = new Service(userRepository, prietenieRepository, mesajRepository);


        FXMLLoader fxmlLoader = new FXMLLoader(UsersApplication.class.getResource("users-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());


        UsersController usersController = fxmlLoader.getController();
        usersController.setService(service);

        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
