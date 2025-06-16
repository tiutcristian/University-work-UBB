import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler

# Load the dataset
file_path = "WA_Fn-UseC_-Telco-Customer-Churn.csv"  # Update with your path if needed
df = pd.read_csv(file_path)

# Drop customerID column if it exists (not useful for modeling)
if 'customerID' in df.columns:
    df.drop(columns=['customerID'], inplace=True)

# Convert 'TotalCharges' to numeric (it may have spaces or non-numeric values)
df['TotalCharges'] = pd.to_numeric(df['TotalCharges'], errors='coerce')

# Fill missing values (if any) with the median for numerical columns
df.fillna(df.median(numeric_only=True), inplace=True)

# Identify categorical and numerical columns
categorical_cols = df.select_dtypes(include=['object']).columns
numerical_cols = df.select_dtypes(include=['int64', 'float64']).columns

# Encode categorical variables as integer labels
label_encoders = {}
for col in categorical_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le  # Store encoder if needed for inverse transformation

# Scale numerical features using StandardScaler
scaler = StandardScaler()
df[numerical_cols] = scaler.fit_transform(df[numerical_cols])

# Display the processed dataset
print(df.head())

# Save the processed dataset (optional)
df.to_csv("processed_telco_churn.csv", index=False)
