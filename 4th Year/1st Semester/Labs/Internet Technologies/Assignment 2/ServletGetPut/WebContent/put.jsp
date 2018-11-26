<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.alert {
    padding: 20px;
    background-color: #008000;
    color: white;
}

.closebtn {
    margin-left: 15px;
    color: white;
    font-weight: bold;
    float: right;
    font-size: 22px;
    line-height: 20px;
    cursor: pointer;
    transition: 0.3s;
}

.closebtn:hover {
    color: black;
}
</style>
</head>
<body>

<%
	out.println("Local port : " + request.getLocalPort());
	out.println("Remote port : " + request.getRemotePort());
	out.println("Server port :" + request.getServerPort());
	out.println("remote adress :" + request.getRemoteAddr());
	out.println("local addr :" + request.getLocalAddr());
%>

<div class="alert">
  <span class="closebtn" onclick="this.parentElement.style.display='none';">&times;</span> 
  <strong>Data Inserted!</strong>
</div>

</body>
</html>