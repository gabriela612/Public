import domain.Utilizator;
import domain.validators.UtilizatorValidator;
import repository.InMemoryRepository;
import repository.Repository;

import java.sql.*;

public class Curs {
    public void main() {
        //Repository<Long, Utilizator> utilizatorRepository =
            //new UserDBRepository(url, userName);
    }
    String url = "jdbc:postgresql://localhost:7777/postgres";
    String userName = "postgres";
    String parola = "MeyYaXrg";
    Repository<Long, Utilizator> utilizatorRepository =
            new InMemoryRepository<Long, Utilizator>(UtilizatorValidator.getInstance());
    public void findAll() throws SQLException {
        Connection connection = DriverManager.getConnection(url, userName, parola);
        Statement statement= connection.prepareStatement("select * from users");
        ResultSet resultSet = statement.executeQuery("select * from users");
        while (resultSet.next()) {
            Long id = resultSet.getLong("id");
            String firstName = resultSet.getString("first_name");
            String lastName = resultSet.getString("last_name");
            Utilizator utilizator = new Utilizator(firstName, lastName);
            utilizator.setId(id);
            System.out.println(utilizator);
            utilizatorRepository.save(utilizator);
        }
    }
    public void findOne(Long id) throws SQLException {
        try (Connection connection = DriverManager.getConnection(url, userName, parola)) {
            PreparedStatement statement = connection.prepareStatement("select * from users where id = ?");
            statement.setInt(1, Math.toIntExact(id));
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                Utilizator utilizator = new Utilizator(firstName, lastName);
                utilizator.setId(id);
                System.out.println(utilizator);
            }
        }
        catch (Exception e) {System.out.println(e); };
    }
}
