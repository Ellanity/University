import matplotlib.pyplot as plt  # for charts
import numpy as np  # for tensors
import pandas as pd
import seaborn as sns
import statsmodels.api as sm
from statsmodels.regression import linear_model
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.pipeline import make_pipeline
from sklearn.model_selection import train_test_split
from sklearn import metrics

# Connecting a dataset, deleting all rows except the first ten thousand
PATH = "glassdoor_gender_pay_gap.csv"
DATASET_SIZE_MAX = 30000
dataset = pd.read_csv(PATH)
dataset = dataset.head(DATASET_SIZE_MAX)

# drops
# sns.heatmap(round(abs(dataset.corr()),1,),annot=True)
# plt.show()

dataset = dataset.drop("JobTitle", axis=1)
dataset = dataset.drop("Gender", axis=1)
dataset = dataset.drop("Education", axis=1)
# ### dataset = dataset.drop("PerfEval", axis=1)
dataset = dataset.drop("Dept", axis=1)
dataset = dataset.drop("Seniority", axis=1)
dataset = dataset.drop("Bonus", axis=1)
""""""

x_train, x_test, y_train, y_test = train_test_split(
    dataset.drop("BasePay", axis=1), dataset["BasePay"],
    test_size=0.2, random_state=0
)
x_train = sm.add_constant(x_train)
sm_ols = linear_model.OLS(y_train, x_train)
sm_model = sm_ols.fit()
print(sm_model.summary())
x_test = sm.add_constant(x_test)
y_pred = sm_model.predict(x_test)
df = pd.DataFrame({"Актуальные значения": y_test,
                   "Предсказанные значения": y_pred})
print(df)
print("Средняя абсолютная ошибка (МАЕ): ",
      metrics.mean_absolute_error(y_test, y_pred))
print("Средняя квадратичная ошибка: ",
      metrics.mean_squared_error(y_test, y_pred))
print("Корень средней квадратичной ошибки (RMSE): ",
      np.sqrt(metrics.mean_squared_error(y_test, y_pred)))
# accuracy = metrics.accuracy_score(y_pred, y_test)
# print(f"Точность модели на тестовом участке = {accuracy}")

# matrix = np.triu(dataset.corr())
sns.heatmap(round(abs(dataset.corr()), 1,), annot=True) #, mask=matrix)
plt.show()

""""""
# remove '\xa0' from lines
# for column in dataset.columns:
#     dataset[column] = dataset[column].str.split().str.join("")
#     dataset[column] = pd.to_numeric(dataset[column])

# plotting charts based on available data
sns.set_style("darkgrid")
sns.set_palette("Set3")
sns.lineplot(x=dataset["BasePay"], y=dataset["Age"])
plt.title("График зависимости")
plt.xlabel("Параметр BasePay")
plt.ylabel("Параметр Age")
plt.show()

# The model provided by the sklearn library accepts only tensors
# of dimension (data set length, 1) as input and output.
# The code below changes the dimension of the source data
x = np.array(dataset["BasePay"]).reshape(-1, 1)
y = np.array(dataset["Age"]).reshape(-1, 1)

# Creating a model where the DEGREES variable denotes the degree of the polynomial.
# the standard error of the model prediction is calculated.
DEGREES = 2
regression = make_pipeline(PolynomialFeatures(DEGREES), LinearRegression())
regression.fit(x, y)
predictions = regression.predict(x)
mean_squared_error = np.mean((predictions - np.array(y)) ** 2)

print(f"Среднеквадратическая ошибка = {mean_squared_error}")

# Plotting charts comparing reference values and model predictions
sns.lineplot(x=dataset["BasePay"], y=dataset["Age"], linestyle="solid")
sns.lineplot(x=dataset["BasePay"], y=predictions.reshape(-1), linestyle="dotted")
plt.title(f"График зависимости\n\n"
          f"Сплошная линия - эталонные значения\n"
          f"Точечная линия - предсказания регрессии")
plt.xlabel("Параметр BasePay")
plt.ylabel("Параметр Age")
plt.show()

# Extracting the coefficients of the equation from the model
x_parameters = np.append(
    regression["linearregression"].intercept_[0],
    regression["linearregression"].coef_[0][1:])
print(x_parameters)
