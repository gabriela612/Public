package org.example.retea_login;

import org.example.retea_login.mesaje.ConversatieController;
import org.example.retea_login.mesaje.MainMesajeController;
import org.example.retea_login.prieteni.*;
import javafx.collections.FXCollections;
import javafx.collections.ObservableArray;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.domain.Utilizator;
import org.example.repository.paging.Page;
import org.example.repository.paging.Pageable;
import org.example.service.Service;
import org.example.utils.event.Event;
import org.example.utils.event.UserChangeEventType;
import org.example.utils.event.UsersChangeEvent;
import org.example.utils.observer.Observer;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UsersController implements Observer<Event> {
    private Service service;

    private Utilizator utilizator;
    private Stage stage;

    public void setService(Service service, Utilizator ut, Stage stage){
        this.service = service;
        this.utilizator = ut;
        this.stage = stage;
        this.service.addObserver(this);
    }

    public void handleDeleteUser(){
        Optional<Utilizator> deleted = service.rmUtilizator(utilizator.getId());
        if (deleted.isPresent())
            MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Delete", "Utilizatorul a fost sters cu succes!");
        this.handleCancel();
    }

    @FXML
    public void handleUpdateUser() {
        initUserEdit(utilizator);
    }

    public void initUserEdit(Utilizator utilizator){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UserController.class.getResource("user-view.fxml"));
            Stage stage = new Stage();
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);

            // Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Utilizator");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            dialogStage.setScene(scene);

            UserController userController = fxmlLoader.getController();

            userController.setService(service, dialogStage, utilizator);
            dialogStage.show();

            //service.removeObserver(userController);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void handlePrieteni() {
        initPrieteni(this.utilizator);
    }

    public void initPrieteni(Utilizator utilizator){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UserController.class.getResource("prieteni/main-prieteni-view.fxml"));
            Stage stage = new Stage();
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);

             //Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle(utilizator.getFullName());
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            dialogStage.setScene(scene);

            MainPrieteniController mainPrieteniController = fxmlLoader.getController();

            mainPrieteniController.setService(service, dialogStage, utilizator);
            dialogStage.show();

            //service.removeObserver(userController);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void handleMesaje() {

        initMesaje(utilizator);
    }

    public void initMesaje(Utilizator utilizator){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UserController.class.getResource("mesaje/main-mesaje-view.fxml"));
            Stage stage = new Stage();
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);

            // Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Mesaje " + utilizator.getFullName());
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            dialogStage.setScene(scene);

            MainMesajeController mainMesajeController = fxmlLoader.getController();

            mainMesajeController.setService(service, dialogStage, utilizator);
            dialogStage.show();

            //service.removeObserver(userController);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void handleCancel(){
        service.removeObserver(this);
        stage.close();
    }

    @Override
    public void update(Event event) {
        if (event instanceof UsersChangeEvent) {
            UsersChangeEvent userEvent = (UsersChangeEvent) event;
            if (Objects.equals(userEvent.getData().getId(), utilizator.getId())) {
                if (userEvent.getType() == UserChangeEventType.DELETE)
                    this.handleCancel();
                if (userEvent.getType() == UserChangeEventType.UPDATE)
                    utilizator = userEvent.getData();
            }
        }
    }
}

