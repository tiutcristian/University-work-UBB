using System.Security.Claims;
using Lab8ASP.Services;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace Lab8ASP.Controllers
{
    [AllowAnonymous]
    public class AccountController : Controller
    {
        private readonly NewsService _service = new NewsService();

        public IActionResult Login() => View();

        [HttpPost]
        public async Task<IActionResult> LoginAsync(string username, string password)
        {
            if (_service.ValidateUser(username, password))
            {
                await HttpContext.SignInAsync
                (
                    CookieAuthenticationDefaults.AuthenticationScheme,
                    new ClaimsPrincipal(new ClaimsIdentity(new[]
                    {
                        new Claim(ClaimTypes.Name, username)
                    }, CookieAuthenticationDefaults.AuthenticationScheme))
                );
                return RedirectToAction("Index", "News");
            }
            ViewBag.Message = "Invalid credentials";
            return View();
        }

        public async Task<IActionResult> LogoutAsync()
        {
            await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
            return RedirectToAction("Index", "News");
        }
    }
}