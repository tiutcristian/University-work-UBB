import { Routes } from '@angular/router';
import { LoginComponent } from './login/login.component';
import { NewsListComponent } from './news-list/news-list.component';
import { NewsFormComponent } from './news-form/news-form.component';

export const routes: Routes = [
  { path: 'login', component: LoginComponent },
  { path: 'news', component: NewsListComponent },
  { path: 'add', component: NewsFormComponent },
  { path: 'edit/:id', component: NewsFormComponent },
  { path: '', redirectTo: 'news', pathMatch: 'full' }
];
