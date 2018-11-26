import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class GetDataServlet
 */
@WebServlet("/get")
public class GetDataServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public GetDataServlet() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#service(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// TODO Auto-generated method stub
		try {
			PrintWriter out = response.getWriter();
			String username = request.getParameter("username");
			String password = request.getParameter("password");
			System.out.print("Username : " + username);
			System.out.print("Passowrd : " + password);
			String sql1 = "select * from users where username='" + username + "'";
			PreparedStatement select1;
			Connection conn = (Connection) getServletContext().getAttribute("DBConnection");
			select1 = conn.prepareStatement(sql1);
			ResultSet result1 = select1.executeQuery();
			result1.last();
			int count = result1.getRow();
			result1.beforeFirst();
			if (count > 0) {
				// User exists
				result1.next();
				if (result1.getString("password").equals(password)) {
					String sql2 = "select * from items where gender='" + result1.getString("gender") + "' and type="
							+ result1.getString("preference");
					PreparedStatement select2;
					select2 = conn.prepareStatement(sql2);
					ResultSet result2 = select2.executeQuery();
					request.setAttribute("result", result2);
					RequestDispatcher rd = request.getRequestDispatcher("get_data.jsp");
					rd.forward(request, response);
				} else {
					out.println("<h1>Wrong Password</h1>");
				}
			} else {
				// User doesn't exist
				out.println("<h1>User doesn't exist</h1>");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
