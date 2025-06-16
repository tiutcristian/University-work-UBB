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


@WebServlet("/vote")
public class VoteServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session == null || session.getAttribute("userId") == null) {
            response.sendRedirect("login.jsp");
            return;
        }

        int voterId = (Integer) session.getAttribute("userId");
        int pictureId = Integer.parseInt(request.getParameter("pictureId"));
        int voteValue = Integer.parseInt(request.getParameter("voteValue"));

        try (Connection conn = DatabaseUtil.getConnection()) {
            // Check if the picture belongs to the voter
            PreparedStatement checkStmt = conn.prepareStatement(
                    "SELECT user_id FROM pictures WHERE picture_id = ?");
            checkStmt.setInt(1, pictureId);
            ResultSet rs = checkStmt.executeQuery();

            if (rs.next() && rs.getInt("user_id") == voterId) {
                request.setAttribute("error", "You cannot vote for your own picture");
                request.getRequestDispatcher("home.jsp").forward(request, response);
                return;
            }

            // Insert or update vote
            PreparedStatement stmt = conn.prepareStatement(
                    "INSERT INTO votes (picture_id, voter_id, vote_value) VALUES (?, ?, ?) " +
                            "ON DUPLICATE KEY UPDATE vote_value = ?");
            stmt.setInt(1, pictureId);
            stmt.setInt(2, voterId);
            stmt.setInt(3, voteValue);
            stmt.setInt(4, voteValue);
            stmt.executeUpdate();

            response.sendRedirect("home");
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}
