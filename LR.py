from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
import pandas as pd

#read in data
data = pd.read_csv('Data.csv', header=None)
data = data.iloc[1:].values
X = data[:,:24]
y = data[:,24]

#split data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)

#standardize data
sc = StandardScaler()
sc.fit(X_train)
X_train_std = sc.transform(X_train)
X_test_std = sc.transform(X_test)

#Find the best C to use for LR
best = [-1, -1]
for i in range(5000):
    av = 0;
    for j in range(100):
        lr = LogisticRegression(C=1+i, random_state=0)
        lr.fit(X_train_std, y_train)
        y_pred = lr.predict(X_test_std)
        av += accuracy_score(y_test, y_pred) / 100
    if av > best[0]:
        best = [av, i+1];

#With this method, we get at best 48% success ratio - worse than 50/50
