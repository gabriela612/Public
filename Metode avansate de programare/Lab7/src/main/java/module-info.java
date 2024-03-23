module org.example.labsapte {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;
    requires java.sql;
    //requires javafx.base;


    opens org.example.labsapte to javafx.fxml, javafx.base;
    exports org.example.labsapte;


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

    opens org.example.labsapte.prieteni to javafx.fxml, javafx.base;
    exports org.example.labsapte.prieteni;

    opens org.example.labsapte.mesaje to javafx.fxml, javafx.base;
    exports org.example.labsapte.mesaje;
}