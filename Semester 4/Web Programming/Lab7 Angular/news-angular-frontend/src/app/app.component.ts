import { HttpClient } from '@angular/common/http';
import { Component, NgModule } from '@angular/core';
import { RouterModule, RouterOutlet } from '@angular/router';
import { NewsListComponent } from "./news-list/news-list.component";
import { NewsFormComponent } from "./news-form/news-form.component";

@Component({
  selector: 'app-root',
  imports: [
    RouterOutlet
],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
// Removed @NgModule decorator as it is incompatible with @Component
export class AppComponent {
  title = 'news-angular-frontend';
}
