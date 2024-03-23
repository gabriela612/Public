package org.example.retea_login.mesaje;

import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;
import org.example.domain.Prietenie;
import org.example.domain.StarePrietenie;
import org.example.domain.Tuple;
import org.example.domain.Utilizator;
import org.example.retea_login.MessageBox;
import org.example.service.Service;
import org.example.utils.event.Event;
import org.example.utils.event.PrieteniChangeEvent;
import org.example.utils.event.UsersChangeEvent;
import org.example.utils.observer.Observer;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class SendMesajController implements Observer<Event> {
    private Service service;
    public Stage stage;
    private Utilizator utilizator;
    @FXML
    TableView<Tuple<Utilizator, Prietenie>> allFriendsTable;

    @FXML
    TableColumn<Tuple<Utilizator, Prietenie>, String> allNumePrieten;

    ObservableList<Tuple<Utilizator, Prietenie>> model = FXCollections.observableArrayList();

    @FXML
    TableView<Tuple<Utilizator, Prietenie>> selFriendsTable;

    @FXML
    TableColumn<Tuple<Utilizator, Prietenie>, String> selNumePrieten;

    ObservableList<Tuple<Utilizator, Prietenie>> selmodel = FXCollections.observableArrayList();

    @FXML
    TextArea textMesajNou;
    public void setService(Service service, Stage stage, Utilizator utilizator){
        this.service = service;
        this.service.addObserver(this);
        this.stage = stage;
        this.utilizator = utilizator;
        initModel();
    }

    @FXML
    public void initialize(){
        allNumePrieten.setCellValueFactory(entity -> {
            return new SimpleObjectProperty<>(entity.getValue().getLeft().getFullName());
        });

        allFriendsTable.setItems(model);


        selNumePrieten.setCellValueFactory(entity -> {
            return new SimpleObjectProperty<>(entity.getValue().getLeft().getFullName());
        });

        selFriendsTable.setItems(selmodel);
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
        selmodel.setAll(new ArrayList<>());
    }

    @Override
    public void update(Event event) {
        if (event instanceof PrieteniChangeEvent || event instanceof UsersChangeEvent)
        {
            initModel();
            MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Modificare"
                    , "A avut loc o modificare, iar datele din acesta pagina sunt actualizate.");
        }
    }

    @FXML
    public void handleAdd() {
        Tuple<Utilizator, Prietenie> selected = allFriendsTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error"
                    , "NU ati selectat nici un utilizator");
        }
        this.selmodel.add(selected);
        this.model.remove(selected);
    }

    @FXML
    public void handleRm() {
        Tuple<Utilizator, Prietenie> selected = selFriendsTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error"
                    , "NU ati selectat nici un utilizator");
        }
        this.selmodel.remove(selected);
        this.model.add(selected);
    }

    @FXML
    public void handleSave() {
        String text = this.textMesajNou.getText();
        if (text.equals("")) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Date insuficiente"
                    , "Nu ati introdus textul mesajului.");
            return;
        }
        if (selmodel.size() == 0) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Date insuficiente"
                    , "Trebuie sa adaugati cel putin un destinatar.");
            return;
        }

        List<Long> to = selmodel.stream()
                .map(tuplu -> tuplu.getLeft().getId())
                .toList();

        try {
            this.service.addMesaj(this.utilizator.getId(), to, text, null);
        } catch (SQLException e) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Opeartion Status", "Operation failed. Please try again");
            return;
        }
        MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Operatie reusita", "Adaugarea s-a efectuat cu succes.");
        this.handleCancel();
    }

    @FXML
    public void handleCancel(){
        service.removeObserver(this);
        stage.close();
    }

}
