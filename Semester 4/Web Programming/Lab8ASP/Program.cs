using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc.Authorization;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddControllersWithViews(options =>
{
    var policy = new AuthorizationPolicyBuilder()
                     .RequireAuthenticatedUser()
                     .Build();
    options.Filters.Add(new AuthorizeFilter(policy));
});
builder.Services.AddSession();
builder.Services.AddAuthentication(CookieAuthenticationDefaults.AuthenticationScheme)
    .AddCookie(options =>
    {
        options.LoginPath = "/Account/Login";
        options.LogoutPath = "/Account/Logout";
        options.AccessDeniedPath = "/Account/AccessDenied";
    });


var app = builder.Build();
app.UseHttpsRedirection();
app.UseRouting();
app.UseAuthorization();
app.UseAuthentication();
app.MapStaticAssets();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=News}/{action=Index}/{id?}")
    .WithStaticAssets();

app.MapControllerRoute(
    name: "news",
    pattern: "{controller=News}/{action=Index}/{id?}",
    defaults: new { controller = "News", action = "Index" })
    .WithStaticAssets();

app.MapControllerRoute(
    name: "news_create",
    pattern: "{controller=News}/{action=Create}/{id?}",
    defaults: new { controller = "News", action = "Create" })
    .WithStaticAssets();

app.MapControllerRoute(
    name: "news_preview",
    pattern: "{controller=News}/{action=Preview}/{id?}",
    defaults: new { controller = "News", action = "Preview" })
    .WithStaticAssets();

app.MapControllerRoute(
    name: "news_edit",
    pattern: "{controller=News}/{action=Edit}/{id?}",
    defaults: new { controller = "News", action = "Edit" })
    .WithStaticAssets();

app.MapControllerRoute(
    name: "login",
    pattern: "{controller=Account}/{action=Login}/{id?}",
    defaults: new { controller = "Account", action = "Login" })
    .WithStaticAssets();

app.UseSession();
app.Run();