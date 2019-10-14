#import threading
#import sys
#try:
#    threading.Lock.release()
#    print ("Try")
#except:
#    sys.exit()
from sklearn.cluster import SpectralClustering
from sklearn.datasets import load_digits

def hello(a):
    #kmeans = KMeans(n_clusters=a)
    #X = [[5,5],[6,6],[-5,-5],[-6,-6]]
    #print (digits.data.shape) 
    labels = SpectralClustering(n_clusters=a).fit_predict(load_digits().data[0].reshape(-1,1))
    #a = 7
    #print (labels)
    return 1


def timeit():
    import time
    s = time.time()
    hello(2)
    hello(2)
    hello(2)
    hello(2)
    hello(2)
    hello(2)
    hello(2)
    hello(2)
    hello(2)
    hello(2)
    e = time.time()
    print ((e-s)/10)
    return 0

#timeit()
