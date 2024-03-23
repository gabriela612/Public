package org.example.labsapte.mesaje;

import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import javafx.util.Callback;
import org.example.domain.Mesaj;
import org.example.domain.Utilizator;
import org.example.labsapte.MessageBox;
import org.example.service.Service;
import org.example.utils.event.Event;
import org.example.utils.observer.Observer;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.StreamSupport;

public class ConversatieController implements Observer<Event> {
    private Service service;
    public Stage stage;
    private Utilizator ut1, ut2;

    @FXML
    TableView<Mesaj> mesajeTable;

    ObservableList<Mesaj> model = FXCollections.observableArrayList();

    @FXML
    TableColumn<Mesaj, String> textMesaj;

    Mesaj mesajSeRaspundeLa;
    @FXML
    Label labelSeRaspundeLa;

    Mesaj currentSelected = null;

    @FXML
    Button buttonReply;

    Mesaj mesajRaspuns = null;
    @FXML
    Label labelRaspuns;

    @FXML
    TextArea textMesajNou;

    public void setService(Service service, Stage stage, Utilizator ut1, Utilizator ut2){
        this.service = service;
        this.service.addObserver(this);
        this.stage = stage;
        this.ut1 = ut1;
        this.ut2 = ut2;
        initModel();
    }

    @Override
    public void update(Event event) {
        initModel();
    }

    @FXML
    public void initialize(){
        textMesaj.setCellValueFactory(entity -> {
            String text = "";
            if (entity.getValue().getRepliesTo() != null)
                text = text.concat("repl. ");
            if (entity.getValue().getIdExpeditor() == ut1.getId())
                text = text.concat("Eu : ");
            else
                text = text.concat(ut2.getFirstName() + " : ");

            text = text.concat(entity.getValue().getText());
            return new SimpleObjectProperty<>(text);
        });

        mesajeTable.setItems(model);
    }

    public void initModel() {
        Iterable<Mesaj> mesajeIterable = service.findAllMesaje(this.ut1.getId(), this.ut2.getId());
        List<Mesaj> mesaje = StreamSupport.stream(mesajeIterable.spliterator(), false)
                .sorted((msg1, msg2) -> {
                    if (msg1.getDataTrimitere().isAfter(msg2.getDataTrimitere()))
                        return 1;
                    if (msg1.getDataTrimitere().equals(msg2.getDataTrimitere()))
                        return 0;
                    return -1;
                })
                .toList();
        model.setAll(mesaje);
    }

    public void handleReply() {
        Mesaj selected = mesajeTable.getSelectionModel().getSelectedItem();
        if (selected == null)
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error"
                    , "NU ati selectat nici un mesaj");
        if (Objects.equals(this.buttonReply.getText(), "Reply"))
        {
            reply(selected);
        }
        else {
            unreply();
        }
    }

    public void reply(Mesaj mesaj) {
        this.mesajSeRaspundeLa = mesaj;
        this.labelSeRaspundeLa.setText(mesaj.getText());
    }

    public void unreply() {
        this.mesajSeRaspundeLa = null;
        this.labelSeRaspundeLa.setText("");
    }

    @FXML
    public void handleSelectionChanged() {
        Mesaj selected = mesajeTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            this.currentSelected = null;
            return;
        }
        if (selected == this.mesajSeRaspundeLa) {
            this.buttonReply.setText("Unreply");
        }
        else
            this.buttonReply.setText("Reply");
        if (!selected.equals(mesajRaspuns)) {
            mesajRaspuns = selected;
            if (selected.getRepliesTo() != null)
            {
                Iterable<Mesaj> mesajeIterable = service.findAllMesaje(this.ut1.getId(), this.ut2.getId());
                Mesaj msg = StreamSupport.stream(mesajeIterable.spliterator(), false)
                        .filter(mesaj -> {
                            return mesaj.getId().getLeft() == selected.getRepliesTo();
                        })
                        .toList().get(0);
                labelRaspuns.setText(msg.getText());
            }
            else
                labelRaspuns.setText("");
        }
    }

    @FXML
    public void handleSave() {
        String text = this.textMesajNou.getText();
        if (text.equals("")) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Date insuficiente"
                    , "Nu ati introdus textul mesajului.");
            return;
        }
        ArrayList<Long> to = new ArrayList<>();
        to.add(ut2.getId());

        try {
            Long idReply = null;
            if (this.mesajSeRaspundeLa != null)
                idReply = this.mesajSeRaspundeLa.getId().getLeft();
            this.service.addMesaj(this.ut1.getId(), to, text, idReply);
        } catch (SQLException e) {
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Opeartion Status", "Operation failed. Please try again");
            return;
        }
        MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Operatie reusita", "Adaugarea s-a efectuat cu succes.");
        return;
    }
}
