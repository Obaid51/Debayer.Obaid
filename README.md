# Debayer

The debayer process/service that has a requirement on a proprietary library: Cuvi. This can only be installed on 2 workstations (license and hardware dependant) and either Linux or Windows. We also utilise VCPKG as the dependency manager for this project. 

## Debayer Process
![Debayer Process](/images/DebayerProcess.png)

## The goals:

The goals are to build this so that it can be deployed in a Linux Container on a GPU based host