package imagesapp;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@WebServlet("/auth")
public class AuthServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String action = request.getParameter("action");

        if ("login".equals(action)) {
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            try (Connection conn = DatabaseUtil.getConnection()) {
                PreparedStatement stmt = conn.prepareStatement(
                        "SELECT user_id FROM users WHERE username = ? AND password = ?");
                stmt.setString(1, username);
                stmt.setString(2, password);  // In production, use password hashing

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    int userId = rs.getInt("user_id");
                    HttpSession session = request.getSession();
                    session.setAttribute("userId", userId);
                    session.setAttribute("username", username);
                    response.sendRedirect("home");
                } else {
                    request.setAttribute("error", "Invalid credentials");
                    request.getRequestDispatcher("login.jsp").forward(request, response);
                }
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        } else if ("logout".equals(action)) {
            request.getSession().invalidate();
            response.sendRedirect("login.jsp");
        }
    }
}
