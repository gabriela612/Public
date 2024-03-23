package org.example.labsapte;

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
            id.setText(this.utilizator.getId().toString());
            firstName.setText(this.utilizator.getFirstName());
            lastName.setText(this.utilizator.getLastName());
            id.setText(utilizator.getId().toString());
        }
    }

    @FXML
    public void handleSaveUser() {
        String newFirstName = firstName.getText();
        String newLastName = lastName.getText();

        if (!UtilizatorValidator.validareNumeUtilizator(newFirstName, newLastName)) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error", "Input gresit !");
        }

        if(this.utilizator == null){
            // means we are doing a create operation
            Optional<Utilizator> newUser = Optional.empty();

            try {
                newUser = service.addUtilizator(newFirstName, newLastName);
            } catch (SQLException e) {
                MessageBox.showMessage(null, Alert.AlertType.ERROR, "Opeartion Status", "Operation failed. Please try again");
                return;
            }
            MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Operation Status", "SUCCESS");
            handleCancel();
        }
        else {
            Long sameId = Long.parseLong(id.getText());
            try {
                Optional<Utilizator> updatedUser = service.updateUtilizator(newFirstName, newLastName, sameId);
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
