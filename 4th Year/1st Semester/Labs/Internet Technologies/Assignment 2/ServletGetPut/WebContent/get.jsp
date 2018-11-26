<%@ page language="java" import="java.util.*" import="java.sql.*" import="javax.servlet.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
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
</head>
<body>

<%
	out.println("Local port : " + request.getLocalPort());
	out.println("Remote port : " + request.getRemotePort());
	out.println("Server port :" + request.getServerPort());
%>

<table id="customers">
  <tr>
    <th>Key</th>
    <th>Value</th>
  </tr>
  <!-- Table contents below -->
  <%
  	ResultSet result = (ResultSet)request.getAttribute("result");
  	String str;
	if (result.next()) {
		str = "<tr><td>" + result.getString("key") + "</td><td>" + result.getString("val") + "</td></tr>";
		out.println(str);
	} else {
		str = "<tr><td>" + result.getString("key") + "</td><td>" + "NULL" + "</td></tr>";
		out.println(str);
	}
  %>
</table>

</body>
</html>