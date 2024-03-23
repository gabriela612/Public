package org.example.retea_login;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.example.domain.Utilizator;
import org.example.domain.validators.UtilizatorValidator;
import org.example.service.Service;
import org.example.utils.event.Event;
import org.example.utils.event.UsersChangeEvent;
import org.example.utils.observer.Observer;

import java.sql.SQLException;
import java.util.Optional;

public class UserController implements Observer<Event> {

    @FXML
    public Label id;

    @FXML
    public TextField firstName;

    @FXML
    public TextField lastName;

    @FXML
    public TextField parola;

    private Service service;

    public Stage stage;

    private Utilizator utilizator;


    public void setService(Service service, Stage stage, Utilizator utilizator){
        this.service = service;
        this.service.addObserver(this);
        this.stage = stage;
        this.utilizator = utilizator;
        initialiseTextFields();
    }

    public void initialiseTextFields(){
        if (this.utilizator != null)
        {
            firstName.setText(this.utilizator.getFirstName());
            lastName.setText(this.utilizator.getLastName());
            id.setText(utilizator.getId().toString());
            parola.setText("");
            parola.setEditable(false);
        }
    }

    @FXML
    public void handleSaveUser() {
        String newFirstName = this.firstName.getText();
        String newLastName = this.lastName.getText();
        String newParola = this.parola.getText();

        if (newFirstName == null || newLastName == null || newParola == null)
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error", "Nu ati completat toate campurile !");
        if (!UtilizatorValidator.validareNumeUtilizator(newFirstName, newLastName)) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error", "Input gresit !");
        }

        if(this.utilizator == null){
            // means we are doing a create operation
            Optional<Utilizator> newUser = Optional.empty();

            try {
                newUser = service.addUtilizator(newFirstName, newLastName, newParola);
                MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Operation Status", "ID-ul noului utilizator este : " + newUser.get().getId() +
                        "\nVa rugam sa tineti minte acest ID deoarece este necesar la log in.");
            } catch (SQLException e) {
                MessageBox.showMessage(null, Alert.AlertType.ERROR, "Opeartion Status", "Operation failed. Please try again");
                return;
            }
            handleCancel();
        }
        else {
            Long sameId = Long.parseLong(id.getText());
            try {
                Optional<Utilizator> updatedUser = service.updateUtilizator(newFirstName, newLastName, sameId, newParola);
            } catch (SQLException e) {
                MessageBox.showMessage(null, Alert.AlertType.ERROR, "Opeartion Status", "Operation failed. Please try again");
                return;
            }
            //todo: handle logic to check if updated
            MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Operation Status", "SUCCESS");
            handleCancel();
        }
    }

    @FXML
    public void handleCancel(){
        service.removeObserver(this);
        stage.close();
    }

    @Override
    public void update(Event usersChangeEvent) {

    }
}
