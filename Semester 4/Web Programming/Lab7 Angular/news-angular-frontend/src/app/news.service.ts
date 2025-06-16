import { HttpClient } from '@angular/common/http';
import { inject, Injectable } from '@angular/core';

@Injectable({ providedIn: 'root' })
export class NewsService {
  apiUrl = 'http://localhost/news/';
  private http = inject(HttpClient);

  getNews() {
    return this.http.get(`${this.apiUrl}get_news.php`);
  }
  
  getNewsById(id: number) {
    return this.http.get(`${this.apiUrl}get_news_by_id.php?id=${id}`);
  }

  getFilteredNews(category: string, start: string, end: string) {
    let params = new URLSearchParams();
    if (category) params.append('category', category);
    if (start) params.append('start', start);
    if (end) params.append('end', end);
    var url = `${this.apiUrl}get_news.php?${params.toString()}`;
    return this.http.get(url);
  }

  addNews(news: any) {
    return this.http.post(`${this.apiUrl}insert_news.php`, news);
  }

  editNews(news: any) {
    return this.http.post(`${this.apiUrl}update_news.php`, news);
  }

  deleteNews(id: number) {
    return this.http.post(`${this.apiUrl}delete_news.php`, { id: id });
  }

  login(credentials: any) {
    return this.http.post(`${this.apiUrl}login.php`, credentials, { withCredentials: true });
  }

  logout() {
    return this.http.post(`${this.apiUrl}logout.php`, {}, { withCredentials: true });
  }

  isLoggedIn() {
    return this.http.get(`${this.apiUrl}is_logged_in.php`, { withCredentials: true });
  }
}