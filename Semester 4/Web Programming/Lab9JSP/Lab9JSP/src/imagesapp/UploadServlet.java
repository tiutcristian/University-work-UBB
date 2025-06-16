package imagesapp;

import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Part;
import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@WebServlet("/upload")
@MultipartConfig
public class UploadServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session == null || session.getAttribute("userId") == null) {
            response.sendRedirect("login.jsp");
            return;
        }

        int userId = (Integer) session.getAttribute("userId");
        Part filePart = request.getPart("picture");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

        // Save file to server
        String uploadPath = getServletContext().getRealPath("") + File.separator + "uploads";
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) uploadDir.mkdir();

        String uniqueFileName = System.currentTimeMillis() + "_" + fileName;
        filePart.write(uploadPath + File.separator + uniqueFileName);

        // Save to database
        try (Connection conn = DatabaseUtil.getConnection()) {
            PreparedStatement stmt = conn.prepareStatement(
                    "INSERT INTO pictures (user_id, filename) VALUES (?, ?)");
            stmt.setInt(1, userId);
            stmt.setString(2, uniqueFileName);
            stmt.executeUpdate();

            response.sendRedirect("home");
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}
