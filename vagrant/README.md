# Vagrant

This tutorial is designed students through the process of setting up a reasonable environment for Linux environment programming using [Vagrant](http://www.vagrantup.com).

## Install Pre-Requisites

* Download the latest version of [Vagrant](http://www.vagrantup.com) software for your operating system.
* Download the latest version of [VirtualBox](http://virtualbox.org) software for your operating system.

## Configuration files

Each of the project folders, has a vagrant configuration file: `Vagrantfile` which is used for configuration of the vagrant environment.

## Using Vagrant

There are a few commands that you'd need to know to harness the power Vagrant:

* To get the status of a cluster or a node: `vagrant status`
* To start a cluster or a node: `vagrant up`
  * To provision or run the setup (initial script) add the `--provision` flag
* To shutdown down a cluster or a node: `vagrant halt`
* To destroy a cluster or a node: `vagrant destroy`

### Access the cluster

* Windows users, please use [putty.exe](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html) to log into the guest OS.  The `host` and `port` information is shown when you boot up the guest OS.

```
==> node1: Waiting for machine to boot. This may take a few minutes...
    node1: SSH address: 127.0.0.1:2222
    node1: SSH username: vagrant
    node1: SSH auth method: private key
```

In the above output, the `host` is `127.0.0.1` and the port is `2222`.

* Mac or Linux users, please type `vagrant ssh node1`, for example, to access `node1`.

Note that while it's tempting to use `VirtualBox` GUI to get into the nodes, we do not recommend this approach.  Instead rely solely on your `putty.exe` or `ssh` application.
