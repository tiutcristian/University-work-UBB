using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Logging;

namespace Lab8ASP.Views.News
{
    public class Edit : PageModel
    {
        private readonly ILogger<Edit> _logger;

        public Edit(ILogger<Edit> logger)
        {
            _logger = logger;
        }

        public void OnGet()
        {
        }
    }
}