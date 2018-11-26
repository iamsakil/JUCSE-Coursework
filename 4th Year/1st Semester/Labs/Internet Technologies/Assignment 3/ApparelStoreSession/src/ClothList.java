import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/clothlist")
public class ClothList extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		try {

			HttpSession session = request.getSession();
			String username = (String) session.getAttribute("username");
			String sql1 = "select * from users where username='" + username + "'";
			PreparedStatement select1;
			Connection conn = (Connection) getServletContext().getAttribute("DBConnection");
			select1 = conn.prepareStatement(sql1);
			ResultSet result1 = select1.executeQuery();
			result1.next();
			String sql2 = "select * from items where gender='" + result1.getString("gender") + "' and type="
					+ result1.getString("preference");
			PreparedStatement select2;
			select2 = conn.prepareStatement(sql2);
			ResultSet result2 = select2.executeQuery();
			request.setAttribute("result", result2);
			RequestDispatcher rd = request.getRequestDispatcher("get_data.jsp");
			rd.forward(request, response);

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}