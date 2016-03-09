Simple Map Reduce program using python.

The examples provided here is taken _en verbaten_ from Tom White's _Hadoop: The Definitive Guide_ .

## Gather data

To gather data from the [NCDC](http://www .ncdc.noaa.gov/) run the `ncdc.sh` script as followed:

```
./ncdc.sh 1940 1950
```

The first argument is the starting year, the second argument is the ending year.

## Copy Data to the Cluster

To copy the data to the hadoop cluster:

```
hadoop fs -copyFromLocal ncdc_data ncdc_data
```
## Running the MapReduce Stream

```
sh run.sh
```

## Copying Data from the Cluster

```
hadoop fs -copyToLocal output output
```


Reference:

* [ncdc.sh](https://gist.github.com/rehevkor5/2e407950ca687b36fc54)
* [Hadoop: The Definitive Guide](http://www.amazon.com/Hadoop-Definitive-Guide-Tom-White/dp/1449311520)

