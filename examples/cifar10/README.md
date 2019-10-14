# CIFAR-10

The CIFAR-10 database is a large database of labeled images that is often used to introduce aspiring data scientists and machine learning enthusiasts to the world of neural networks. As such, it is also a great place to start showing off the power and versatility that the CML library offers.

I you don't already have the Eigen library installed, you can download it from [the official Eigen website] and move it to `/usr/local/include` so that your compiler knows that it exists.

To start, first you must download the dataset from the official website. This can be done using the following script:

```bash
mkdir -p data
wget https://www.cs.toronto.edu/~kriz/cifar-10-binary.tar.gz -q -o /dev/null -P data/
gunzip data/cifar-10-binary.tar.gz
```

Now that you have the dataset downloaded and prepared to go, you must compile the mnist example to run anything.

```bash
make
./cifar10
```

Running the above, you will see the verbose style output. The accuracies can be summed up as:

![Accuracy](accuracy.png)

Evidently, it does very well.
