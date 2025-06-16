using Dapper;
using Lab8ASP.Data;
using Lab8ASP.Models;
using Npgsql;

namespace Lab8ASP.Services
{
    public class NewsService
    {
        public List<News> GetNews(DateTime? from, DateTime? to, string? category)
        {
            var newsList = new List<News>();
            var query = "SELECT * FROM news WHERE 1=1";

            if (!string.IsNullOrEmpty(category))
                query += " AND category = @Category";

            if (from.HasValue)
                query += " AND date >= @StartDate";

            if (to.HasValue)
                query += " AND date <= @EndDate";


            using (var connection = DbConnectionFactory.getConnection())
            {
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                if (!string.IsNullOrEmpty(category))
                    command.Parameters.AddWithValue("@Category", category);

                if (from.HasValue)
                    command.Parameters.AddWithValue("@StartDate", from.Value);

                if (to.HasValue)
                    command.Parameters.AddWithValue("@EndDate", to.Value);

                using var reader = command.ExecuteReader();
                while (reader.Read())
                {
                    newsList.Add(new News
                    {
                        Id = Convert.ToInt32(reader["Id"]),
                        Title = reader["Title"]?.ToString() ?? string.Empty,
                        Text = reader["Text"]?.ToString() ?? string.Empty,
                        Producer = reader["Producer"]?.ToString() ?? string.Empty,
                        Date = Convert.ToDateTime(reader["Date"]),
                        Category = reader["Category"]?.ToString() ?? string.Empty
                    });
                }
            }
            return newsList;
        }

        public void AddNews(News news)
        {
            using var conn = DbConnectionFactory.getConnection();
            conn.Open();
            var sql = "INSERT INTO news (title, text, producer, date, category) VALUES (@Title, @Text, @Producer, @Date, @Category)";
            conn.Execute
            (
                sql,
                new
                {
                    news.Title,
                    news.Text,
                    news.Producer,
                    news.Date,
                    Category = news.Category.ToString()
                }
            );
        }

        public void UpdateNews(News news)
        {
            using var conn = DbConnectionFactory.getConnection();
            conn.Open();
            var sql = "UPDATE news SET title=@Title, text=@Text, producer=@Producer, date=@Date, category=@Category WHERE id=@Id";
            conn.Execute
            (
                sql,
                new
                {
                    news.Title,
                    news.Text,
                    news.Producer,
                    news.Date,
                    Category = news.Category.ToString(),
                    news.Id
                }
            );
        }

        public void DeleteNews(int id)
        {
            using var conn = DbConnectionFactory.getConnection();
            conn.Open();
            conn.Execute("DELETE FROM news WHERE id = @id", new { id });
        }

        public News? GetNewsById(int id)
        {
            using var conn = DbConnectionFactory.getConnection();
            conn.Open();
            return conn.QueryFirstOrDefault<News>("SELECT * FROM news WHERE id = @id", new { id });
        }

        public bool ValidateUser(string username, string password)
        {
            using var conn = DbConnectionFactory.getConnection();
            conn.Open();
            var user = conn.QueryFirstOrDefault<User>("SELECT * FROM users WHERE username = @username AND password = @password", new { username, password });
            return user != null;
        }
    }
}