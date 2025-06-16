using Microsoft.Data.SqlClient;
using Npgsql;

namespace Lab8ASP.Data
{
    public class DbConnectionFactory
    {
        private const string ConnectionString = "Host=localhost;Port=5432;Username=postgres;Password=;Database=lab8aspweb";
        public static NpgsqlConnection getConnection()
        {
            return new NpgsqlConnection(ConnectionString);
        }
    }
}