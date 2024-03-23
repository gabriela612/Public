package org.example.retea_login.prieteni;

import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.domain.Prietenie;
import org.example.domain.StarePrietenie;
import org.example.domain.Tuple;
import org.example.domain.Utilizator;
import org.example.domain.validators.UtilizatorValidator;
import org.example.retea_login.MessageBox;
import org.example.retea_login.UserController;
import org.example.service.Service;
import org.example.utils.event.Event;
import org.example.utils.event.PrieteniChangeEvent;
import org.example.utils.event.UsersChangeEvent;
import org.example.utils.observer.Observer;

import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class SugestiiPrieteniController implements Observer<Event> {
    private Service service;
    public Stage stage;

    @FXML
    TableView<Utilizator> friendsTable;

    @FXML
    TableColumn<Utilizator, String> prenumePrieten;

    @FXML
    TableColumn<Utilizator, String> numePrieten;

    @FXML
    Button buttonAici;

    ObservableList<Utilizator> model = FXCollections.observableArrayList();

    private Utilizator utilizator;

    public void setService(Service service, Stage stage, Utilizator utilizator){
        this.service = service;
        this.service.addObserver(this);
        this.stage = stage;
        this.utilizator = utilizator;
        initModel();
    }

    @FXML
    public void initialize(){
        prenumePrieten.setCellValueFactory(entity -> {
            return new SimpleObjectProperty<>(entity.getValue().getFirstName());
        });

        numePrieten.setCellValueFactory(entity -> {
            return new SimpleObjectProperty<>(entity.getValue().getLastName());
        });

        //prenumePrieten.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        //numePrieten.setCellValueFactory(new PropertyValueFactory<>("lastName"));

        friendsTable.setItems(model);
        buttonAici.setDisable(true);
    }

    public void initModel(){
        Iterable<Tuple<Utilizator, Prietenie>> friendsIterable = service.findAllPrieteni(utilizator.getId());
        List<Utilizator> friends = StreamSupport.stream(friendsIterable.spliterator(), false)
                .map(Tuple::getLeft)
                .collect(Collectors.toList());
        Iterable<Utilizator> allUsers = service.findAllUsers();
        List<Utilizator> sugestii = StreamSupport.stream(allUsers.spliterator(),  false)
                .filter(user -> {
                    if (user.getId() == utilizator.getId())
                        return false;
                    if (!friends.contains(user))
                        return true;
                    boolean rej = StreamSupport.stream(friendsIterable.spliterator(), false)
                            .filter(el -> {
                                return el.getRight().getStare() == StarePrietenie.rejected &&
                                        (el.getRight().getId().getRight() == user.getId() ||
                                                el.getRight().getId().getLeft() == user.getId());
                            }).count() != 0;
                    boolean acc = StreamSupport.stream(friendsIterable.spliterator(), false)
                            .filter(el -> {
                                return el.getRight().getStare() != StarePrietenie.rejected &&
                                        (el.getRight().getId().getRight() == user.getId() ||
                                                el.getRight().getId().getLeft() == user.getId());
                            }).count() == 0;
                    return rej && acc;
        }).collect(Collectors.toList());
        model.setAll(sugestii);
    }

    @Override
    public void update(Event event) {
        if (event instanceof PrieteniChangeEvent || event instanceof UsersChangeEvent)
            initModel();
    }

    @FXML
    public void handleAddPrieten() {

        Utilizator selected = (Utilizator) friendsTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            Long id1 = this.utilizator.getId();
            Long id2 = selected.getId();
            Optional<Prietenie> deleted = Optional.empty();
            try {
                deleted = service.addPrietenie(id1, id2);
            } catch (SQLException e) {
                MessageBox.showMessage(null, Alert.AlertType.ERROR, "Error", "Ceva nu a mers. Incerca din nou.");
            }
            if (deleted.isPresent())
                MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "ADD", "Cererea a fost trimisa cu succes!");
        } else MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error", "Nu ati selectat nici un utilizator!");

    }

    public void initMain(){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UserController.class.getResource("prieteni/main-prieteni-view.fxml"));

            Scene scene = new Scene(fxmlLoader.load());
            this.stage.setScene(scene);

//            Stage stage = new Stage();
//            Scene scene = new Scene(fxmlLoader.load());
//            stage.setScene(scene);
//
//            //Create the dialog Stage.
//            Stage dialogStage = new Stage();
//            dialogStage.setTitle("Prieteni");
//            dialogStage.initModality(Modality.WINDOW_MODAL);
//            dialogStage.initOwner(this.stage);
//            dialogStage.setScene(scene);

            MainPrieteniController mainPrieteniController = fxmlLoader.getController();

            mainPrieteniController.setService(service, stage, utilizator);
            stage.show();

            //service.removeObserver(userController);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void initCereri() {
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UserController.class.getResource("prieteni/cereri-prietenie-view.fxml"));

            Scene scene = new Scene(fxmlLoader.load());
            this.stage.setScene(scene);

//            Stage stage = new Stage();
//            Scene scene = new Scene(fxmlLoader.load());
//            stage.setScene(scene);
//
//            //Create the dialog Stage.
//            Stage dialogStage = new Stage();
//            dialogStage.setTitle("Prieteni");
//            dialogStage.initModality(Modality.WINDOW_MODAL);
//            dialogStage.initOwner(this.stage);
//            dialogStage.setScene(scene);

            CereriPrietenieController cereriPrietenieController = fxmlLoader.getController();

            cereriPrietenieController.setService(service, stage, utilizator);
            stage.show();

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
}
