<%--
  Created by IntelliJ IDEA.
  User: cristiantiut
  Date: 29.05.2025
  Time: 16:37
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="jakarta.tags.core" prefix="c" %>
<html>
<head>
  <title>Picture Voting System</title>
</head>
<body>
<h1>Welcome, ${sessionScope.username}!</h1>

<%--initially get pictures from request attributes--%>
<c:set var="topN" value="${param.topN != null ? param.topN : 5}" />
<c:set var="topPictures" value="${requestScope.topPictures}" />
<c:set var="pictures" value="${requestScope.pictures}" />

<form action="auth?action=logout" method="post">
  <input type="submit" value="Logout">
</form>

<h2>Upload a Picture</h2>
<form action="upload" method="post" enctype="multipart/form-data">
  <input type="file" name="picture" accept="image/*" required>
  <input type="submit" value="Upload">
</form>

<h2>Top ${topN} Pictures</h2>
<form action="home" method="get">
  Show top <input type="number" name="topN" min="1" value="${topN}"> pictures
  <input type="submit" value="Update">
</form>
<table border="1">
  <tr>
    <th>Rank</th>
    <th>Picture</th>
    <th>Author</th>
    <th>Votes</th>
  </tr>

  <c:forEach items="${topPictures}" var="picture" varStatus="loop">
    <tr>
      <td>${loop.index + 1}</td>
      <td><img src="uploads/${picture.filename}" height="100"></td>
      <td>${picture.username}</td>
      <td>${picture.totalVotes}</td>
    </tr>
  </c:forEach>
</table>

<h2>All Pictures</h2>
<table border="1">
  <tr>
    <th>Picture</th>
    <th>Author</th>
    <th>Votes</th>
    <th>Action</th>
  </tr>
  <c:forEach items="${pictures}" var="picture">
    <tr>
      <td><img src="uploads/${picture.filename}" height="100"></td>
      <td>${picture.username}</td>
      <td>${picture.totalVotes}</td>
      <td>
        <c:if test="${!picture.isOwner}">
          <form action="vote" method="post">
            <input type="hidden" name="pictureId" value="${picture.pictureId}">
            Vote: <input type="number" name="voteValue" min="1" value="1" required>
            <input type="submit" value="Vote">
          </form>
        </c:if>
        <c:if test="${picture.isOwner}">
          (Your picture)
        </c:if>
      </td>
    </tr>
  </c:forEach>
</table>
</body>
</html>
