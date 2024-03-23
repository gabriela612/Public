module org.example.labsapte {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;
    requires java.sql;
    //requires javafx.base;


    opens org.example.retea_login to javafx.fxml, javafx.base;
    exports org.example.retea_login;


    opens org.example.service.config to javafx.fxml, javafx.base;
    exports org.example.service.config;

    opens org.example.service to javafx.fxml, javafx.base;
    exports org.example.service;

    opens org.example.domain to javafx.fxml, javafx.base;
    exports org.example.domain;

    opens org.example.utils.event to javafx.fxml, javafx.base;
    exports org.example.utils.event;

    opens org.example.utils.observer to javafx.fxml, javafx.base;
    exports org.example.utils.observer;

    opens org.example.retea_login.prieteni to javafx.fxml, javafx.base;
    exports org.example.retea_login.prieteni;

    opens org.example.retea_login.mesaje to javafx.fxml, javafx.base;
    exports org.example.retea_login.mesaje;
}