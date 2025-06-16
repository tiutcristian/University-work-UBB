using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Lab8ASP.Models
{
    public class User
    {
        public required string Username { get; set; }
        public required string Password { get; set; }
    }
}