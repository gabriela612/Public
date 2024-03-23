package org.example.labsapte.prieteni;

import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.domain.Prietenie;
import org.example.domain.StarePrietenie;
import org.example.domain.Tuple;
import org.example.domain.Utilizator;
import org.example.labsapte.MessageBox;
import org.example.labsapte.UserController;
import org.example.service.Service;
import org.example.utils.event.Event;
import org.example.utils.event.PrieteniChangeEvent;
import org.example.utils.event.UsersChangeEvent;
import org.example.utils.observer.Observer;

import java.io.IOException;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class MainPrieteniController implements Observer<Event> {
    private Service service;
    public Stage stage;

    @FXML
    TableView<Tuple<Utilizator, Prietenie>> friendsTable;

    @FXML
    TableColumn<Tuple<Utilizator, Prietenie>, String> prenumePrieten;

    @FXML
    TableColumn<Tuple<Utilizator, Prietenie>, String> numePrieten;

    @FXML
    Button buttonAici;

    ObservableList<Tuple<Utilizator, Prietenie>> model = FXCollections.observableArrayList();

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
            return new SimpleObjectProperty<>(entity.getValue().getLeft().getFirstName());
        });

        numePrieten.setCellValueFactory(entity -> {
            return new SimpleObjectProperty<>(entity.getValue().getLeft().getLastName());
        });

        //prenumePrieten.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        //numePrieten.setCellValueFactory(new PropertyValueFactory<>("lastName"));

        friendsTable.setItems(model);
        buttonAici.setDisable(true);

    }

    public void initModel(){
        Iterable<Tuple<Utilizator, Prietenie>> moviesIterable = service.findAllPrieteni(utilizator.getId());
        List<Tuple<Utilizator, Prietenie>> users = StreamSupport.stream(moviesIterable.spliterator(),
                        false)
                .filter(elem -> {
                    return elem.getRight().getStare() == StarePrietenie.approved;
                })
                .collect(Collectors.toList());
        model.setAll(users);
    }

    @Override
    public void update(Event event) {
        if (event instanceof PrieteniChangeEvent || event instanceof UsersChangeEvent)
            initModel();
    }

    public void handleDeletePrieten(){
        Tuple<Utilizator, Prietenie> selected = (Tuple<Utilizator, Prietenie>)
                friendsTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            Long id1 = selected.getLeft().getId();
            Long id2 = this.utilizator.getId();
            Optional<Prietenie> deleted = service.rmPrietenie(id1, id2);
            if (deleted.isPresent())
                MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Delete", "Prietenia a fost stearsa cu succes!");
        } else MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error", "Nu ati selectat nici un utilizator!");
    }

    public void initSugestii(){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(UserController.class.getResource("prieteni/sugestii-prieteni-view.fxml"));

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

            SugestiiPrieteniController sugestiiPrieteniController = fxmlLoader.getController();

            sugestiiPrieteniController.setService(service, stage, utilizator);
            stage.show();

            //service.removeObserver(userController);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void initCereri(){
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
