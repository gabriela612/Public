package org.example.labsapte;

import org.example.labsapte.mesaje.ConversatieController;
import org.example.labsapte.mesaje.MainMesajeController;
import org.example.labsapte.prieteni.*;
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
import org.example.utils.event.UsersChangeEvent;
import org.example.utils.observer.Observer;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UsersController implements Observer<Event> {
    @FXML
    TableView<Utilizator> usersTable;

    @FXML
    TableColumn<Utilizator, Long> idUtilizator;

    @FXML
    TableColumn<Utilizator, String> firstName;

    @FXML
    TableColumn<Utilizator, String> lastName;

    ObservableList<Utilizator> model = FXCollections.observableArrayList();

    private Service service;

    @FXML
    Button previousButton;

    @FXML
    Button nextButton;

    private int currentPage=0;
    private int numberOfRecordsPerPage = 5;

    private int totalNumberOfElements;

    @FXML
    ComboBox<Integer> comboBoxNumberOfRecordsPerPage;

    public void setService(Service service){
        this.service = service;
        this.service.addObserver(this);
        initModel();
    }

    @FXML
    public void initialize(){
        idUtilizator.setCellValueFactory(new PropertyValueFactory<>("id"));
        firstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));

        usersTable.setItems(model);
        ObservableList<Integer> observableListNumbers = FXCollections.observableArrayList();
        for (int i = 3; i <= 7; i ++)
            observableListNumbers.add(i);
        comboBoxNumberOfRecordsPerPage.setItems(observableListNumbers);

    }

    public void initModel(){
//        Iterable<Utilizator> moviesIterable = service.findAllUsers();
//        List<Utilizator> users = StreamSupport.stream(moviesIterable.spliterator(), false).toList();
//        model.setAll(users);

        Page<Utilizator> usersOnCurrentPage = service.findAllUsers(new Pageable(currentPage, numberOfRecordsPerPage));
        totalNumberOfElements = usersOnCurrentPage.getTotalNumberOfElements();
        List<Utilizator> usersList = StreamSupport.stream(usersOnCurrentPage.getElementsOnPage().spliterator(), false).toList();
        //System.out.println(usersList);
        model.setAll(usersList);
        handlePageNavigationChecks();
    }

    @Override
    public void update(Event usersChangeEvent) {
        if (usersChangeEvent instanceof UsersChangeEvent)
            initModel();
    }

    public void handleDeleteUser(){
        Utilizator selected = (Utilizator) usersTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            Optional<Utilizator> deleted = service.rmUtilizator(selected.getId());
            if (deleted.isPresent())
                MessageBox.showMessage(null, Alert.AlertType.INFORMATION, "Delete", "Utilizatorul a fost sters cu succes!");
        } else MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error", "Nu ati selectat nici un utilizator!");
    }

    @FXML
    public void handleUpdateUser() {
        Utilizator selected = usersTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            initUserEdit(selected);
        } else
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error"
                    , "NU ati selectat nici un utilizator");
    }

    @FXML
    public void handleSaveUser() {
        initUserEdit(null);
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

        Utilizator selected = usersTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            initPrieteni(selected);
        } else
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error"
                    , "NU ati selectat nici un utilizator");
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

        Utilizator selected = usersTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            initMesaje(selected);
        } else
            MessageBox.showMessage(null, Alert.AlertType.ERROR, "Selection error"
                    , "NU ati selectat nici un utilizator");
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

    void test() {
        ListView<Utilizator> listView = new ListView<>();
        ObservableList observableList = (ObservableList<Utilizator>)
                StreamSupport.stream(service.findAllUsers().spliterator(), false).toList();
        listView.setItems(observableList);
    }

    private void handlePageNavigationChecks(){
        previousButton.setDisable(currentPage == 0);
        nextButton.setDisable((currentPage+1)*numberOfRecordsPerPage >= totalNumberOfElements);
    }
    public void goToNextPage(ActionEvent actionEvent) {
        System.out.println("NEXT PAGE");
        currentPage++;
        initModel();
    }

    public void goToPreviousPage(ActionEvent actionEvent) {
        System.out.println("PREVIOUS PAGE");
        currentPage--;
        initModel();
    }

    @FXML
    public void changeNumberOfRecordsPerPage() {
        this.currentPage = 0;
        this.numberOfRecordsPerPage = this.comboBoxNumberOfRecordsPerPage.getValue();
        this.initModel();
    }
}


//    @FXML
//    ImageView imageView;

//    public void Image()
//    {
//        Image image = null;
//        try {
//            image = new Image(getClass().getResource("pika.jpeg").openStream());
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
//        BackgroundImage img = new BackgroundImage(image, BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT,
//                BackgroundSize.DEFAULT);
//        Background background = new Background(img);
//        //imageView.setImage(img);
//
//    }