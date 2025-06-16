import { Component, inject, ViewChild } from '@angular/core';
import { NewsService } from '../news.service';
import { ActivatedRoute, RouterModule } from '@angular/router';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-news-form',
  imports: [
    CommonModule, 
    RouterModule
  ],
  templateUrl: './news-form.component.html',
  styleUrl: './news-form.component.css'
})
export class NewsFormComponent {
  id: any;
  route = inject(ActivatedRoute);
  newsService = inject(NewsService);
  @ViewChild('title') title: any;
  @ViewChild('text') text: any;
  @ViewChild('producer') producer: any;
  @ViewChild('date') date: any;
  @ViewChild('category') category: any;

  ngOnInit() {
    this.id = this.route.snapshot.paramMap.get('id');
    if (this.id) {
      // fetch and prefill form
      console.log('Editing news with ID:', this.id);

      this.newsService.getNewsById(this.id).subscribe({
        next: (news: any) => {
          this.title.nativeElement.value = news.title;
          this.text.nativeElement.value = news.text;
          this.producer.nativeElement.value = news.producer;
          this.date.nativeElement.value = news.date;
          this.category.nativeElement.value = news.category;
        },
        error: (err: any) => {
          // handle error
          alert(`Error fetching news: ${err.message}`);
        }
      });
    } else {
      console.log('Creating new news');
    }
  }
  
  onSubmit() {
    if (this.id) {
        this.newsService.editNews({
            id: this.id,
            title: this.title.nativeElement.value,
            text: this.text.nativeElement.value,
            producer: this.producer.nativeElement.value,
            date: this.date.nativeElement.value,
            category: this.category.nativeElement.value
        }).subscribe({
        next: (response: any) => {
          // handle success
          if (response.status == "success") {
            console.log('News updated successfully');

          } else {
            alert(`Error updating news: ${response.error}`);
          }
        },
        error: (err) => {
          // handle error
          alert(`Error updating news: ${err.message}`);
        }
      });
    }
    else this.newsService.addNews({
      title: this.title.nativeElement.value,
      text: this.text.nativeElement.value,
      producer: this.producer.nativeElement.value,
      date: this.date.nativeElement.value,
      category: this.category.nativeElement.value
    }).subscribe({
      next: (response: any) => {
        // handle success
        if (response.status == "success") {
          console.log('News added successfully');
        } else {
          alert(`Error adding news: ${response.error}`);
        }
      },
      error: (err) => {
        // handle error
        alert(`Error adding news: ${err.message}`);
      }
    });
  }
}
