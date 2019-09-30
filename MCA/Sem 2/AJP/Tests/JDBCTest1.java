import java.sql.*;


/**
 * Java Data Base Connectivity
 * 	Testing for database connectivity and displaying 
 * 		the result set from a database table.
*/
/* Accesses MS Access DB: filename=StudentDB.accdb; DB name=StudentDB_096 */
public class JDBCTest1 {
	public static void main(String[] args) {
		String driver = "sun.jdbc.odbc.JdbcOdbcDriver";
		// change this to whatever your DSN is
		String dataSourceName = "stud";
		String dbURL = "jdbc:odbc:" + dataSourceName;
		String userName = "";
		String password = "";
		
		try {
			Class.forName(driver);
			Connection con = DriverManager.getConnection(dbURL, userName, password);
			Statement st = con.createStatement();
			String query = "select ID, Name from Student";
			ResultSet rs = st.executeQuery(query);

			while(rs.next()) {
				System.out.printf("%4d \t %-10s \n", rs.getInt("ID"), rs.getString("Name"));			
			}
		} catch(Exception e) {
			System.err.println("Error: " + e);
			e.printStackTrace(System.err);
		}
	}
}