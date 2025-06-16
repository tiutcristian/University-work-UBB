data = pd.read_csv("WA_Fn-UseC_-Telco-Customer-Churn.csv")

data.drop(columns=["customerID"], inplace=True)

enc = preprocessing.OrdinalEncoder(encoded_missing_value=-1)
encdata = enc.fit_transform(data)

scaler = preprocessing.StandardScaler()
scaleddata = scaler.fit_transform(encdata)

scaleddata