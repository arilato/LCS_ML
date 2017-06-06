from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
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


svm = SVC(kernel='rbf', random_state=0)
svm.fit(X_train_std, y_train)
y_pred = svm.predict(X_test_std)
print(accuracy_score(y_pred, y_test))

#59.25% success rate -> better than 50/50
