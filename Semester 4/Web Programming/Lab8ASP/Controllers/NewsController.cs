using Microsoft.AspNetCore.Mvc;
using Lab8ASP.Models;
using Lab8ASP.Services;
using Microsoft.AspNetCore.Authorization;

namespace Lab8ASP.Controllers;

public class NewsController : Controller
{
    private readonly NewsService _service = new NewsService();

    public IActionResult Index(DateTime? from, DateTime? to, string? category)
    {
        ViewBag.From = from;
        ViewBag.To = to;
        ViewBag.Category = category;
        var news = _service.GetNews(from, to, category);
        return View(news);
    }

    public IActionResult Create() => View();

    [HttpPost]
    public IActionResult Create(News news)
    {
        try
        {
            _service.AddNews(news);
            return RedirectToAction("Index");
        }
        catch (Exception ex)
        {
            @ViewBag.Error = ex.Message;
            return View(news);
        }
    }

    public IActionResult Preview(int id)
    {
        var news = _service.GetNewsById(id);
        return View(news);
    }

    public IActionResult Edit(int id)
    {
        var news = _service.GetNewsById(id);
        return View(news);
    }

    [HttpPost]
    public IActionResult Edit(News news)
    {
        try
        {
            _service.UpdateNews(news);
        return RedirectToAction("Index");
        }
        catch (Exception ex)
        {
            @ViewBag.Error = ex.Message;
            return View(news);
        }
    }

    public IActionResult Delete(int id)
    {
        _service.DeleteNews(id);
        return RedirectToAction("Index");
    }
}
