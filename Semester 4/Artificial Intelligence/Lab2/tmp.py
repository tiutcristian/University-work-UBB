import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression, Ridge, Lasso, ElasticNet

# Load data
data = pd.read_csv('student_study_hours.csv')

X = np.array(data['Hours']).reshape(-1, 1)
y = np.array(data['Scores'])

# Split data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=0)

# Train models
lr = LinearRegression().fit(X_train, y_train)
ridge = Ridge(alpha=1.0).fit(X_train, y_train)
lasso = Lasso(alpha=0.1).fit(X_train, y_train)
elastic_net = ElasticNet(alpha=0.1, l1_ratio=0.5).fit(X_train, y_train)

# Predictions
pred_hours = np.array([[2], [5], [8]])
pred_lr = lr.predict(pred_hours)
pred_ridge = ridge.predict(pred_hours)
pred_lasso = lasso.predict(pred_hours)
pred_elastic_net = elastic_net.predict(pred_hours)

# Best fit lines
x = np.linspace(min(X), max(X), 100).reshape(-1, 1)
line_lr = lr.predict(x)
line_ridge = ridge.predict(x)
line_lasso = lasso.predict(x)
line_elastic_net = elastic_net.predict(x)

# Plot results
plt.figure(figsize=(8, 6))
plt.scatter(X_train, y_train, color='blue', label='Train Data')
plt.scatter(X_test, y_test, color='red', label='Test Data')
plt.plot(x, line_lr, color='green', label='Linear Regression')
plt.plot(x, line_ridge, color='orange', linestyle='dashed', label='Ridge')
plt.plot(x, line_lasso, color='purple', linestyle='dotted', label='Lasso')
plt.plot(x, line_elastic_net, color='brown', linestyle='dashdot', label='Elastic Net')
plt.scatter(pred_hours, pred_lr, color='green', marker='x', s=100, label='LR Predictions')
plt.scatter(pred_hours, pred_ridge, color='orange', marker='x', s=100, label='Ridge Predictions')
plt.scatter(pred_hours, pred_lasso, color='purple', marker='x', s=100, label='Lasso Predictions')
plt.scatter(pred_hours, pred_elastic_net, color='brown', marker='x', s=100, label='Elastic Net Predictions')
plt.xlabel('Hours Studied')
plt.ylabel('Scores')
plt.title('Student Study Hours with Regularization')
plt.legend()
plt.show()

