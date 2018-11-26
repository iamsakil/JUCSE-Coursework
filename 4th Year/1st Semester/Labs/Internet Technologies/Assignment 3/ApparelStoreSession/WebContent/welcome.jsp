<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<title>Servlet based Apparrel Store</title>
<meta content="noindex, nofollow" name="robots">
<!-- Include CSS File Here -->
<link href="form1.css" rel="stylesheet">
</head>
<body>
	<%
		response.setHeader("Cache-Control","no-cache,no-store,must-revalidate");
		if(session.getAttribute("username")==null){
			response.sendRedirect("index.html");
		}
	%>
	<form action="clothlist">
	<div>
		<input type="submit" value="Show Cloth List">
	</div>
	</form>
	<form action="logout">
	<div>
		<input type="submit" value="Log Out">
	</div>
	</form>
</body>
</html>