using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Logging;

namespace Lab8ASP.Views.News
{
    public class Preview : PageModel
    {
        private readonly ILogger<Preview> _logger;

        public Preview(ILogger<Preview> logger)
        {
            _logger = logger;
        }

        public void OnGet()
        {
        }
    }
}