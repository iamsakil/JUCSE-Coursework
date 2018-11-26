package com.sakilmallick;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class GetServlet
 */
@WebServlet("/get")
public class GetServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public GetServlet() {
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
			String key = request.getParameter("key");
			String sql = "select key,val from mydb where key='" + key + "'";
			PreparedStatement select;
			Connection conn = (Connection) getServletContext().getAttribute("DBConnection");
			select = conn.prepareStatement(sql);
			ResultSet result = select.executeQuery();
			request.setAttribute("result", result);
			RequestDispatcher rd = request.getRequestDispatcher("get.jsp");
			rd.forward(request, response);
//			out.println("Local port : " + request.getLocalPort());
//			out.println("Remote port : " + request.getRemotePort());
//			out.println("Server port :" + request.getServerPort());
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
