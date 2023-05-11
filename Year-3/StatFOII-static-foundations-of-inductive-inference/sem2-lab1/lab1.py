import pandas as pd
import seaborn as sns
from sklearn import metrics
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
import matplotlib.pyplot as plt


pd.options.display.max_columns = None
PATH = "citrus.csv"
choice=''
dataset = pd.read_csv(PATH)
#dataset = dataset.drop('name' , axis=1)
#print(dataset.head())
train_input, test_input, train_output, test_output=0,0,0,0

for column in dataset:
    if type(dataset[column][0]) is str:
        dataset[column] = pd.factorize(dataset[column])[0]

print(' 1 - Show heatmap \n 2 - Train \n 3 - Predict and show accuracy')

while(True):
    choice=input()
    if(choice=='1'):
        sns.heatmap(round(abs(dataset.corr()),1,),annot=True)
        plt.show()
    elif (choice == '2'):
        train_input, test_input, train_output, test_output = train_test_split(
            dataset.drop('name', axis=1),
            dataset["name"],
            test_size=0.3
        )
    elif (choice == '3'):
        model = GaussianNB()
        model.fit(train_input, train_output)
        predictions = model.predict(test_input)
        print(predictions[:20])
        accuracy = metrics.accuracy_score(predictions, test_output)
        print(f"Точность модели на тестовом участке = {accuracy}")
