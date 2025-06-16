import { Component, inject, ViewChild } from '@angular/core';
import { NewsService } from '../news.service';
import { Router } from '@angular/router';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-login',
  imports: [CommonModule],
  templateUrl: './login.component.html',
  styleUrl: './login.component.css'
})
export class LoginComponent {
  @ViewChild('username') username: any;
  @ViewChild('password') password: any;
  private newsService = inject(NewsService);
  private router = inject(Router);
  errorMessage = '';

  ngOnInit() {
    this.newsService.isLoggedIn().subscribe((data: any) => {
      if (data) {
        this.router.navigate(['/news']);
      }
    });
  }
  
  onSubmit() {
    console.log('Login form submitted');

    this.newsService.login({
      username: this.username.nativeElement.value,
      password: this.password.nativeElement.value
    }).subscribe({
      next: (data: any) => {
        if (data.status === 'success') {
          this.router.navigate(['/news']);
        } else {
          this.errorMessage = data.message;
        }
      },
      error: (error: any) => {
        this.errorMessage = 'An error occurred during login';
      }
    });
  }
}
