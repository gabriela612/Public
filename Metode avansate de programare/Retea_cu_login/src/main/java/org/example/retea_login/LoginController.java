package org.example.retea_login;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.domain.Utilizator;
import org.example.domain.validators.UtilizatorValidator;
import org.example.retea_login.prieteni.CereriPrietenieController;
import org.example.service.Service;
import org.example.utils.Criptare;

import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.sql.SQLException;
import java.util.Objects;
import java.util.Optional;

public class LoginController {
    @FXML
    public TextField idField;

    @FXML
    public TextField parolaField;

    private Service service;
    private Stage stage;

    public void setService(Service service, Stage stage){
        this.service = service;
        this.stage = stage;
    }

    @FXML
    public void handleLogIn() throws NoSuchAlgorithmException {
        if (Objects.equals(idField.getText(), "") || Objects.equals(parolaField.getText(), "")) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error"
                    , "NU ati introdus date in toate casetele de text.");
            return;
        }
        Long idCitit = Long.parseLong(idField.getText());
        String parolaCitita = parolaField.getText();
        if (parolaCitita.length() < 8) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error"
                    , "Parola trebuie sa aiba minim 8 caractere");
            return;
        }
        Optional<Utilizator> utilizator = this.service.findUser(idCitit);
        if (utilizator.isEmpty()) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error"
                    , "ID-ul introdus nu a fost gasit.");
            return;
        }
        if (!Objects.equals(utilizator.get().getParola(), Criptare.Cri(parolaCitita))) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error"
                    , "Parola incorecta.");
            return;
        }
        initUsers(utilizator.get());
    }

    public void initUsers(Utilizator ut) {
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UsersController.class.getResource("users-view.fxml"));

            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);
            UsersController usersController = fxmlLoader.getController();

            usersController.setService(service, ut, stage);
            stage.setTitle(ut.getFullName());
            stage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void initUser(){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UserController.class.getResource("user-view.fxml"));

            Stage stage = new Stage();
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);
            UserController userController = fxmlLoader.getController();

            userController.setService(service, stage, null);
            stage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
