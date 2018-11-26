package com.sakilmallick;

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

/**
 * Servlet implementation class PutServlet
 */
@WebServlet("/put")
public class PutServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public PutServlet() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#service(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		try {

			String ke = request.getParameter("key");
			String key = ke + "2";
			String sql = "select key,val from mydb where key='" + key + "'";
			PreparedStatement select;
			Connection conn = (Connection) getServletContext().getAttribute("DBConnection");
			select = conn.prepareStatement(sql);
			ResultSet result = select.executeQuery();
			if (result.next()) {
				RequestDispatcher rd = request.getRequestDispatcher("error.jsp");
				rd.forward(request, response);
			} else {
				String val = request.getParameter("val");
				System.out.println("key : " + key);
				System.out.println("val : " + val);
				PreparedStatement ps = conn.prepareStatement("insert into mydb values(?,?)");
				ps.setString(1, key);
				ps.setString(2, val);
				int ret = ps.executeUpdate();
				if (ret > 0) {
					RequestDispatcher rd = request.getRequestDispatcher("put.jsp");
					rd.forward(request, response);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
