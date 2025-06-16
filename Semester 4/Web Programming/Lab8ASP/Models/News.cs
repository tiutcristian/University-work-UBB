using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Lab8ASP.Models
{

    public class News
    {
        public int Id { get; set; }
        public required string Title { get; set; }
        public required string Text { get; set; }
        public required string Producer { get; set; }
        public DateTime Date { get; set; }
        public required string Category { get; set; }
    }
}