module org.example.tlcgui {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;
    requires java.desktop;

    opens org.example.tlcgui to javafx.fxml;
    exports org.example.tlcgui;
    exports org.example.tlcgui.controllerGUI;
    opens org.example.tlcgui.controllerGUI to javafx.fxml;
}