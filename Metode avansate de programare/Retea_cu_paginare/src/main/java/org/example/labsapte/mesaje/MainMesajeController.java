package org.example.labsapte.mesaje;

import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.domain.Prietenie;
import org.example.domain.StarePrietenie;
import org.example.domain.Tuple;
import org.example.domain.Utilizator;
import org.example.labsapte.MessageBox;
import org.example.labsapte.UserController;
import org.example.labsapte.UsersController;
import org.example.service.Service;
import org.example.utils.event.Event;
import org.example.utils.event.PrieteniChangeEvent;
import org.example.utils.event.UsersChangeEvent;
import org.example.utils.observer.Observer;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class MainMesajeController implements Observer<Event> {
    private Service service;
    public Stage stage;
    @FXML
    TableView<Tuple<Utilizator, Prietenie>> friendsTable;

    @FXML
    TableColumn<Tuple<Utilizator, Prietenie>, String> prenumePrieten;

    @FXML
    TableColumn<Tuple<Utilizator, Prietenie>, String> numePrieten;

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

        friendsTable.setItems(model);

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

    @FXML
    public void handleCancel(){
        service.removeObserver(this);
        stage.close();
    }

    @FXML
    public void handleConversatie() {
        Utilizator selected = friendsTable.getSelectionModel().getSelectedItem().getLeft();
        if (selected != null) {
            initConversatie(selected);
        } else
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error"
                    , "NU ati selectat nici un utilizator");
    }

    public void initConversatie(Utilizator utilizator){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(ConversatieController.class.getResource("conversatie-view.fxml"));
            Stage stage = new Stage();
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);

            // Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Conversatie : " +  this.utilizator.getFullName() + " - "
                    + utilizator.getFullName());
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            dialogStage.setScene(scene);

            ConversatieController conversatieController = fxmlLoader.getController();

            conversatieController.setService(service, dialogStage, this.utilizator, utilizator);
            dialogStage.show();

            //service.removeObserver(userController);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void handleSendMesaj() {
        initSendMesaj();
    }

    public void initSendMesaj(){
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(SendMesajController.class.getResource("send-mesaj-view.fxml"));
            Stage stage = new Stage();
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);

            // Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle(this.utilizator.getFullName() + " sends mesaj");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            dialogStage.setScene(scene);

            SendMesajController sendMesajController = fxmlLoader.getController();

            sendMesajController.setService(service, dialogStage, this.utilizator);
            dialogStage.show();

            //service.removeObserver(userController);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
