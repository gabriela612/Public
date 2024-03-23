package org.example.repository;

import org.example.domain.*;
import org.example.domain.validators.Validator;
import org.example.domain.validators.ValidatorFactory;
import org.example.domain.validators.ValidatorStrategy;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class PrietenieBDRepository implements Repository<Tuple<Long, Long>, Prietenie> {

    private String url;
    private String username;
    private String password;

    private Validator<Prietenie> validator;

    public PrietenieBDRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
        validator = ValidatorFactory.getInstance().create(ValidatorStrategy.prietenie);
    }

    @Override
    public Optional<Prietenie> findOne(Tuple<Long, Long> ids) {

        try(Connection connection = DriverManager.getConnection(url, username, password);) {

            PreparedStatement statement = connection.prepareStatement("select * from prietenii " +
                    "where id1 = ? and id2 = ?");
            statement.setLong(1, ids.getLeft());
            statement.setLong(2, ids.getRight());
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()) {
                LocalDateTime friendFrom = resultSet.getDate("data").
                        toLocalDate().atTime(0,0);
                String stare = resultSet.getString("stare");
                Prietenie p = new Prietenie(ids.getLeft(), ids.getRight(),
                        friendFrom, Prietenie.getStare(stare));
                return Optional.ofNullable(p);
            }
            else {
                statement = connection.prepareStatement("select * from prietenii " +
                        "where id1 = ? and id2 = ?");
                statement.setLong(1, ids.getRight());
                statement.setLong(2, ids.getLeft());
                resultSet = statement.executeQuery();

                if(resultSet.next()) {
                    LocalDateTime friendFrom = resultSet.getDate("data").
                            toLocalDate().atTime(0,0);
                    String stare = resultSet.getString("stare");
                    Prietenie p = new Prietenie(ids.getLeft(), ids.getRight(),
                            friendFrom, Prietenie.getStare(stare));
                    return Optional.ofNullable(p);
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    public Optional<Prietenie> findOne(Tuple<Long, Long> ids, StarePrietenie starePrietenie) {

        try(Connection connection = DriverManager.getConnection(url, username, password);) {

            PreparedStatement statement = connection.prepareStatement("select * from prietenii " +
                    "where id1 = ? and id2 = ? and stare=?");
            statement.setLong(1, ids.getLeft());
            statement.setLong(2, ids.getRight());
            statement.setString(3, Prietenie.getStare(starePrietenie));
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()) {
                LocalDateTime friendFrom = resultSet.getDate("data").
                        toLocalDate().atTime(0,0);
                String stare = resultSet.getString("stare");
                Prietenie p = new Prietenie(ids.getLeft(), ids.getRight(),
                        friendFrom, Prietenie.getStare(stare));
                return Optional.ofNullable(p);
            }
            else {
                statement = connection.prepareStatement("select * from prietenii " +
                        "where id1 = ? and id2 = ? and stare=?");
                statement.setLong(1, ids.getRight());
                statement.setLong(2, ids.getLeft());
                statement.setString(3, Prietenie.getStare(starePrietenie));
                resultSet = statement.executeQuery();

                if(resultSet.next()) {
                    LocalDateTime friendFrom = resultSet.getDate("data").
                            toLocalDate().atTime(0,0);
                    String stare = resultSet.getString("stare");
                    Prietenie p = new Prietenie(ids.getLeft(), ids.getRight(),
                            friendFrom, Prietenie.getStare(stare));
                    return Optional.ofNullable(p);
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    @Override
    public Optional<Prietenie> findOneExact(Tuple<Long, Long> ids) {

        try(Connection connection = DriverManager.getConnection(url, username, password);) {

            PreparedStatement statement = connection.prepareStatement("select * from prietenii " +
                    "where id1 = ? and id2 = ?");
            statement.setLong(1, ids.getLeft());
            statement.setLong(2, ids.getRight());
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()) {
                LocalDateTime friendFrom = resultSet.getDate("data").
                        toLocalDate().atTime(0,0);
                String stare = resultSet.getString("stare");
                Prietenie p = new Prietenie(ids.getLeft(), ids.getRight(),
                        friendFrom, Prietenie.getStare(stare));
                return Optional.ofNullable(p);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    @Override
    public Iterable<Prietenie> findAll() {
        Set<Prietenie> prietenieSet = new HashSet<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("select * from prietenii");
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next())
            {
                Long id1 = resultSet.getLong("id1");
                Long id2 = resultSet.getLong("id2");
                LocalDateTime friendFrom = resultSet.getDate("data").
                        toLocalDate().atTime(0,0);
                String stare = resultSet.getString("stare");
                Prietenie prietenie = new Prietenie(id1, id2, friendFrom, Prietenie.getStare(stare));
                prietenieSet.add(prietenie);

            }
            return prietenieSet;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Prietenie> save(Prietenie entity) throws SQLException {

        validator.validate(entity);

        try (Connection conn = DriverManager.getConnection(url, username, password)) {

            String insert = "INSERT INTO prietenii(id1, id2, data, stare) VALUES (?, ?, ?, ?)";
            PreparedStatement statement = conn.prepareStatement(insert);
            statement.setLong(1, entity.getId().getLeft());
            statement.setLong(2, entity.getId().getRight());
            statement.setDate(3, Date.valueOf(entity.getDate().toLocalDate()));
            statement.setString(4, Prietenie.getStare(entity.getStare()));
            statement.executeUpdate();

        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        //System.out.println(this.findOne(entity.getId()));
        return (this.findOneExact(entity.getId()));
    }

    @Override
    public Optional<Prietenie> delete(Tuple<Long, Long> longLongTuple) {
        Optional<Prietenie> prietenie;
        prietenie = this.findOneExact(longLongTuple);
        if (prietenie.isEmpty()) {
            prietenie = this.findOne(new Tuple<>(longLongTuple.getRight(), longLongTuple.getLeft()));
        }

        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            String sql = "DELETE FROM prietenii WHERE ((id1=? AND id2=?) or (id1=? AND id2=?)) and stare<>?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setLong(1, longLongTuple.getLeft());
            statement.setLong(2, longLongTuple.getRight());
            statement.setLong(3, longLongTuple.getRight());
            statement.setLong(4, longLongTuple.getLeft());
            statement.setString(5, "'" + Prietenie.getStare(StarePrietenie.rejected) + "'");
            statement.executeUpdate();

        } catch (SQLException ex) {
            ex.printStackTrace();
        }

        return prietenie;
    }

    @Override
    public Optional<Prietenie> update(Prietenie entity) {

        validator.validate(entity);

        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            String sql = "UPDATE prietenii SET data=?, stare=? WHERE id1=? and id2=?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setDate(1, Date.valueOf(entity.getDate().toLocalDate()));
            statement.setString(2, Prietenie.getStare(entity.getStare()));
            statement.setLong(3, entity.getId().getLeft());
            statement.setLong(4, entity.getId().getRight());
            statement.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return this.findOneExact(entity.getId());
    }
}
