package org.example.repository;

import org.example.domain.User;
import org.example.domain.Utilizator;
import org.example.domain.validators.Validator;
import org.example.domain.validators.ValidatorFactory;
import org.example.domain.validators.ValidatorStrategy;
import org.example.repository.paging.Page;
import org.example.repository.paging.Pageable;
import org.example.repository.paging.PagingRepository;

import java.sql.*;
import java.util.*;

import static java.lang.Math.toIntExact;

public class UserDBRepository implements PagingRepository<Long, Utilizator> {

    private String url;
    private String username;
    private String password;

    private Validator<Utilizator> validator;


    public UserDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
        validator = ValidatorFactory.getInstance().create(ValidatorStrategy.utilizator);
    }

    @Override
    public Optional<Utilizator> findOne(Long longID) {
        try(Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement("select * from users " +
                    "where id = ?");

        ) {
            statement.setInt(1, Math.toIntExact(longID));
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()) {
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                Utilizator u = new Utilizator(firstName,lastName);
                u.setId(longID);
                return Optional.ofNullable(u);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    @Override
    public Iterable<Utilizator> findAll() {
        Set<Utilizator> users = new HashSet<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("select * from users");
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next())
            {
                Long id= resultSet.getLong("id");
                String firstName=resultSet.getString("first_name");
                String lastName=resultSet.getString("last_name");
                Utilizator user = new Utilizator(firstName,lastName);
                user.setId(id);
                users.add(user);

            }
            return users;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public Optional<Utilizator> save(Utilizator entity) {

        validator.validate(entity);

        try (Connection conn = DriverManager.getConnection(url, username, password)) {

            String insert = "INSERT INTO users(first_name, last_name) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(insert, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.executeUpdate();

            ResultSet res = statement.getGeneratedKeys();

            while (res.next()) {
                Long getGeneratedId = res.getLong(1);
                entity.setId(getGeneratedId);
            }
            return Optional.ofNullable(entity);

        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Utilizator> delete(Long aLong) {

        Optional<Utilizator> utilizator = this.findOne(aLong);

        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            String sql = "DELETE FROM users WHERE id=?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setLong(1, aLong);
            statement.executeUpdate();

        } catch (SQLException ex) {
            ex.printStackTrace();
            return Optional.empty();
        }
        utilizator.get().setId(null);
        return utilizator;
    }

    @Override
    public Optional<Utilizator> update(Utilizator entity) {

        validator.validate(entity);

        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            String sql = "UPDATE users SET first_name=?, last_name=? WHERE id=?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setLong(3, entity.getId());
            statement.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return this.findOne(entity.getId());
    }

    @Override
    public String toString() {
//        return "InMemoryRepository{" +
//                " entities=" + entities +
//                '}';
        String rez = "";
        for (var i : this.findAll()) {
            rez += i.toString() + "\n";
        }
        return rez;
    }

    private int returnNumberOfElements(){
        int numberOfElements=0;
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
             // pas 2: design & execute SLQ
             PreparedStatement statement = conn.prepareStatement("select count(*) as count from users");
             ResultSet resultSet = statement.executeQuery();
            // pas 3: process result set
            while (resultSet.next()){
                numberOfElements = resultSet.getInt("count");
            }
        }
        catch (SQLException e){
            System.out.println(e.getMessage());
        }
        // pas 3: return no elements
        return numberOfElements;
    }

        @Override
    public Page<Utilizator> findAll(Pageable pageable) {
        int numberOfElements = this.returnNumberOfElements();
        int limit = pageable.getPageSize();
        int offset = pageable.getPageSize()*pageable.getPageNumber();
        if(offset >= numberOfElements)
            return new Page<>(new ArrayList<>(), numberOfElements);
        // prereq: create empty set
        List<Utilizator> users = new ArrayList<>();
        // pas 1: conectarea la baza de date
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
             // pas 2: design & execute SLQ
             PreparedStatement statement = conn.prepareStatement("select * from users limit ? offset ?");
            statement.setInt(2, offset);
            statement.setInt(1,limit);
            ResultSet resultSet = statement.executeQuery();
            // pas 3: process result set
            while (resultSet.next()){
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                Utilizator currentUser = new Utilizator(firstName, lastName);
                currentUser.setId(id);
                // add to set of movies
                users.add(currentUser);
            }
        }
        catch (SQLException e){
            System.out.println(e.getMessage());
        }
        // pas 3: return result list
        return new Page<>(users, numberOfElements);
    }
}
