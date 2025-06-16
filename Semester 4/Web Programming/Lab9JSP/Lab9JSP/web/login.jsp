<%--
  Created by IntelliJ IDEA.
  User: cristiantiut
  Date: 30.05.2025
  Time: 02:17
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <title>Login</title>
</head>
<body>
<h1>Login</h1>
<% if (request.getAttribute("error") != null) { %>
<p style="color:red">${error}</p>
<% } %>
<form action="auth" method="post">
  <input type="hidden" name="action" value="login">
  Username: <input type="text" name="username" required><br>
  Password: <input type="password" name="password" required><br>
  <input type="submit" value="Login">
</form>
</body>
</html>
