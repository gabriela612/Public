package org.example.repository;

import org.example.domain.Entity;
import org.example.domain.Mesaj;
import org.example.domain.Tuple;
import org.example.domain.Utilizator;
import org.example.domain.validators.IsNullException;
import org.example.domain.validators.Validator;
import org.example.domain.validators.ValidatorFactory;
import org.example.domain.validators.ValidatorStrategy;

import java.sql.*;
import java.sql.Date;
import java.time.LocalDateTime;
import java.util.*;
import java.util.function.Consumer;

public class MesajDBRepository implements Repository<Tuple<Long, Long>, Mesaj> {

    private String url;
    private String username;
    private String password;

    public MesajDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Mesaj> findOne(Tuple<Long, Long> tuple) {
        Long aLong = tuple.getLeft();
        try(Connection connection = DriverManager.getConnection(url, username, password);) {
            var insert = "select msg.id_ut_ex, " +
                    "msg.data_trimitere, msg.text, msg_pr.id_ut_dest, re_msg.id_mesaj_vechi " +
                    "from mesaje as msg " +
                    "full outer join mesaj_primit as msg_pr " +
                    "on msg_pr.id_mesaj = msg.id_mesaj " +
                    "full outer join reply_mesaj as re_msg " +
                    "on (msg.id_mesaj = re_msg.id_mesaj_nou) " +
                    "where msg.id_mesaj = ?";
            PreparedStatement statement = connection.prepareStatement(insert);

                statement.setLong(1, aLong);
                ResultSet resultSet = statement.executeQuery();
                if(resultSet.next()) {
                    Long idExpeditor = resultSet.getLong("id_ut_ex");
                    LocalDateTime dataTrimitere = resultSet.getTimestamp("data_trimitere")
                            .toLocalDateTime();
                    String text = resultSet.getString("text");
                    Long idDestinatar = resultSet.getLong("id_ut_dest");
                    Long idRepliesTo = resultSet.getLong("id_mesaj_vechi");
                    if (idRepliesTo == 0)
                        idRepliesTo = null;

                    Mesaj m = new Mesaj(idExpeditor, text, idRepliesTo, dataTrimitere);
                    m.setId(tuple);
                    m.addSendTo(idDestinatar);

                    while (resultSet.next()) {
                        idDestinatar = resultSet.getLong("id_ut_dest");
                        m.addSendTo(idDestinatar);
                    }

                    return Optional.ofNullable(m);
                }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    @Override
    public Iterable<Mesaj> findAll() {
        try(Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement("select msg.id_mesaj, " +
                    "msg.id_ut_ex, msg.data_trimitere, msg.text, msg_pr.id_ut_dest, re_msg.id_mesaj_vechi " +
                    "from mesaje as msg " +
                    "full outer join mesaj_primit as msg_pr " +
                    "on msg_pr.id_mesaj = msg.id_mesaj " +
                    "full outer join reply_mesaj as re_msg " +
                    "on (msg.id_mesaj = re_msg.id_mesaj_nou) ");

        ) {
            ResultSet resultSet = statement.executeQuery();
            Map<Long, Mesaj> mesaje = new HashMap<>();
            while (resultSet.next()) {
                Long idMesaj = resultSet.getLong("id_mesaj");
                if (mesaje.get(idMesaj) == null) {
                    Long idExpeditor = resultSet.getLong("id_ut_ex");
                    LocalDateTime dataTrimitere = resultSet.getTimestamp("data_trimitere")
                            .toLocalDateTime();
                    String text = resultSet.getString("text");
                    Long idDestinatar = resultSet.getLong("id_ut_dest");
                    Long idRepliesTo = resultSet.getLong("id_mesaj_vechi");
                    if (idRepliesTo == 0)
                        idRepliesTo = null;

                    Mesaj m = new Mesaj(idExpeditor, text, idRepliesTo, dataTrimitere);
                    m.setId(new Tuple<>(idMesaj, null));
                    m.addSendTo(idDestinatar);

                    mesaje.put(idMesaj, m);
                }
                else {
                    Long idDestinatar = resultSet.getLong("id_ut_dest");
                    mesaje.get(idMesaj).addSendTo(idDestinatar);
                }

            }
            if (mesaje.size() != 0)
                return mesaje.values();
            return null;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Mesaj> save(Mesaj entity) throws SQLException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {

            String insert = "insert into mesaje(id_ut_ex, text, data_trimitere) values(?, ?, ?);";
            PreparedStatement statement = conn.prepareStatement(insert, Statement.RETURN_GENERATED_KEYS);
            statement.setLong(1, entity.getIdExpeditor());
            statement.setString(2, entity.getText());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getDataTrimitere()));
            statement.executeUpdate();

            ResultSet res = statement.getGeneratedKeys();

            while (res.next()) {
                Long getGeneratedId = res.getLong(1);
                entity.setId(new Tuple<>(getGeneratedId, null));
            }

            if (entity.getId() == null || entity.getId().getLeft() == null)
                throw new IsNullException("nu s-a generat nicio cheie");

            if (entity.getRepliesTo() != null) {
                insert = "insert into reply_mesaj(id_mesaj_vechi, id_mesaj_nou) values(?, ?)";
                statement = conn.prepareStatement(insert);
                statement.setLong(1, entity.getRepliesTo());
                statement.setLong(2, entity.getId().getLeft());
                statement.executeUpdate();
            }
            entity.getSendTo().forEach(dest -> inserare_primire(dest, entity.getId().getLeft(), conn));

            return Optional.ofNullable(entity);

        } catch (SQLException ex) {
            System.out.println(ex);
        }
        return Optional.empty();
    }

    @Override
    public Optional<Mesaj> delete(Tuple<Long, Long> tuple) {
        Optional<Mesaj> mesaj = this.findOne(tuple);
        if (mesaj.get().getSendTo().size() == 1) {
            try (Connection conn = DriverManager.getConnection(url, username, password)) {
                String sql = "DELETE FROM mesaje WHERE id_mesaj = ?";
                PreparedStatement statement = conn.prepareStatement(sql);
                statement.setLong(1, tuple.getLeft());
                statement.executeUpdate();

            } catch (SQLException ex) {
                System.out.println(ex);
                return Optional.empty();
            }
        }
        else {
            try (Connection conn = DriverManager.getConnection(url, username, password)) {
                String sql = "DELETE FROM mesaj_primit WHERE id_mesaj = ? and id_ut_dest = ?";
                PreparedStatement statement = conn.prepareStatement(sql);
                statement.setLong(1, tuple.getLeft());
                statement.setLong(2, tuple.getRight());
                statement.executeUpdate();

            } catch (SQLException ex) {
                System.out.println(ex);
                return Optional.empty();
            }
        }
        mesaj.get().setId(null);
        return mesaj;
    }

    @Override
    public Optional<Mesaj> update(Mesaj entity) {
        return Optional.empty();
    }

    private Consumer<Long> inserare_primire(Long id_ut_dest, Long id_mesaj , Connection conn) {
        String ins = "insert into mesaj_primit(id_mesaj, id_ut_dest) values(?, ?)";
        try {
            PreparedStatement statement = conn.prepareStatement(ins);
            statement.setLong(1, id_mesaj);
            statement.setLong(2, id_ut_dest);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return null;
    }
}
