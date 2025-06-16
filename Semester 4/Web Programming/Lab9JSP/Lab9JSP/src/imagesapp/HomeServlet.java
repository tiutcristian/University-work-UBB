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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session == null || session.getAttribute("userId") == null) {
            response.sendRedirect("login.jsp");
            return;
        }

        int userId = (Integer) session.getAttribute("userId");
        int topN = 5; // default
        if (request.getParameter("topN") != null) {
            topN = Integer.parseInt(request.getParameter("topN"));
        }

        try (Connection conn = DatabaseUtil.getConnection()) {
            // Get all pictures with vote totals
            PreparedStatement picturesStmt = conn.prepareStatement(
                    "SELECT p.picture_id, p.filename, u.username, u.user_id, " +
                            "COALESCE(SUM(v.vote_value), 0) AS total_votes " +
                            "FROM pictures p " +
                            "JOIN users u ON p.user_id = u.user_id " +
                            "LEFT JOIN votes v ON p.picture_id = v.picture_id " +
                            "GROUP BY p.picture_id, p.filename, u.username, u.user_id " +
                            "ORDER BY p.upload_date DESC");
            ResultSet picturesRs = picturesStmt.executeQuery();

            List<Map<String, Object>> pictures = new ArrayList<>();
            while (picturesRs.next()) {
                Map<String, Object> picture = new HashMap<>();
                picture.put("pictureId", picturesRs.getInt("picture_id"));
                picture.put("filename", picturesRs.getString("filename"));
                picture.put("username", picturesRs.getString("username"));
                picture.put("userId", picturesRs.getInt("user_id"));
                picture.put("totalVotes", picturesRs.getInt("total_votes"));
                picture.put("isOwner", picturesRs.getInt("user_id") == userId);
                pictures.add(picture);
            }

            // Get top N pictures
            PreparedStatement topPicturesStmt = conn.prepareStatement(
                    "SELECT p.picture_id, p.filename, u.username, " +
                            "COALESCE(SUM(v.vote_value), 0) AS total_votes " +
                            "FROM pictures p " +
                            "JOIN users u ON p.user_id = u.user_id " +
                            "LEFT JOIN votes v ON p.picture_id = v.picture_id " +
                            "GROUP BY p.picture_id, p.filename, u.username " +
                            "ORDER BY total_votes DESC LIMIT ?");
            topPicturesStmt.setInt(1, topN);
            ResultSet topPicturesRs = topPicturesStmt.executeQuery();

            List<Map<String, Object>> topPictures = new ArrayList<>();
            while (topPicturesRs.next()) {
                Map<String, Object> picture = new HashMap<>();
                picture.put("pictureId", topPicturesRs.getInt("picture_id"));
                picture.put("filename", topPicturesRs.getString("filename"));
                picture.put("username", topPicturesRs.getString("username"));
                picture.put("totalVotes", topPicturesRs.getInt("total_votes"));
                topPictures.add(picture);
            }

            request.setAttribute("pictures", pictures);
            request.setAttribute("topPictures", topPictures);
            request.setAttribute("topN", topN);
            request.getRequestDispatcher("home.jsp").forward(request, response);

        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}
