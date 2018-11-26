<%@ page language="java" import="java.util.*" import="java.sql.*" import="javax.servlet.*" import="javax.servlet.http.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
	<style>
	#customers {
	    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
	    border-collapse: collapse;
	    width: 100%;
	}
	
	#customers td, #customers th {
	    border: 1px solid #ddd;
	    padding: 8px;
	}
	
	#customers tr:nth-child(even){background-color: #f2f2f2;}
	
	#customers tr:hover {background-color: #ddd;}
	
	#customers th {
	    padding-top: 12px;
	    padding-bottom: 12px;
	    text-align: left;
	    background-color: #4CAF50;
	    color: white;
	}
	</style>
	<body>
		<h1>Type reference:
		<br>
		1 -> Discounted
		<br>
		2 -> New Arrival
		</h1>
		<table id="customers">
			<tr>
			  <th>Name</th>
			  <th>Price</th>
			  <th>Type</th>
			</tr>
			<!-- Table contents below -->
			<%
				ResultSet result = (ResultSet) request.getAttribute("result");
				String str;
				while (result.next()) {
					str = "<tr><td>" + result.getString("name") + "</td><td> RS. " + result.getString("price") + "</td><td>" + result.getString("type") + "</td></tr>";
					out.println(str);
				}
			%>
		</table>
	</body>
</html>