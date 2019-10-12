from sklearn.cluster import KMeans
from sklearn.datasets import load_digits

def hello(kmeans,digits):
    #kmeans = KMeans(n_clusters=a)
    #X = [[5,5],[6,6],[-5,-5],[-6,-6]]
    #print (digits.data.shape) 
    labels = kmeans.fit_predict(digits.data)
    #a = 7
    #print (labels)
    return 1
