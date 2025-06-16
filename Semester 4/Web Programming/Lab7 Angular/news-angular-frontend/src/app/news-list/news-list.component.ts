import { Component, inject } from '@angular/core';
import { NewsService } from '../news.service';
import { RouterModule } from '@angular/router';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-news-list',
  imports: [
    RouterModule,
    CommonModule
  ],
  templateUrl: './news-list.component.html',
  styleUrl: './news-list.component.css'
})
export class NewsListComponent {

  private newsService = inject(NewsService);
  news: any[] = [];
  isLoggedIn: boolean = false;
  previousFilter = {
    category: '',
    start: '',
    end: ''
  };
  currentFilter = {
    category: '',
    start: '',
    end: ''
  };

  ngOnInit() {
    this.newsService.isLoggedIn().subscribe((data: any) => {
      this.isLoggedIn = data;
    });

    this.newsService.getNews().subscribe((data: any) => {
      this.news = data;
    });
  }

  delete(id: number) {
    if (confirm('Are you sure you want to delete this news?')) {
      this.newsService.deleteNews(id).subscribe({
        next: (data: any) => {
          if (data.status === 'success') {
            this.ngOnInit()
          } else {
            alert(data.message);
          }
        },
        error: (error: any) => {
          alert(`An error occurred during delete: ${error}`);
        }
      });
    }
  }

  logout() {
    this.newsService.logout().subscribe(() => {
      this.ngOnInit();
    });
  }

  onFilterClick() {
    let category = (document.getElementById('categoryFilter') as HTMLInputElement)?.value || '';
    let start = (document.getElementById('startDate') as HTMLInputElement)?.value || '';
    let end = (document.getElementById('endDate') as HTMLInputElement)?.value || '';

    this.newsService.getFilteredNews(category, start, end).subscribe((data: any) => {
      this.news = data;
      // Display the previous filter
      this.previousFilter = {
        category: this.currentFilter.category,
        start: this.currentFilter.start,
        end: this.currentFilter.end
      };
      // Update the previous filter
      this.currentFilter = {
          category: category,
          start: start,
          end: end
      };
    });
  }
}