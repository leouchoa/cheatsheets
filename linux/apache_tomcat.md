# Just Enough Apache Tomcat

## Concepts

Used to server java web apps. Which means **you need to
have java installed**

## Instalation

1. Install java sdk (jdk)
2. Download the tomcat server from the [website](https://tomcat.apache.org/download-10.cgi)

```bash
yum install java-1.8.0-openjdk-devel
wget https://dlcdn.apache.org/tomcat/tomcat-10/v10.1.18/bin/apache-tomcat-10.1.18.tar.gz
tar xvf apache-tomcat-10.1.18.tar.gz
./apache-tomcat-10.1.18.tar.gz/bin/startup.sh
```

## Changing Ports in Apache Tomcat

The configuration is in the `/apache-tomcat-10/conf/server.xml`. To change the port:

```bash
sudo sed -i 's/8081/9090/g'  /opt/apache-tomcat-8/conf/server.xml;
```

To shutdown the tomcat server:

```bash
sudo /opt/apache-tomcat-8/bin/shutdown.sh
```

To start the tomcat server:

```bash
sudo /opt/apache-tomcat-8/bin/startup.sh
```

and then run

```bash
curl localhost:9090; ps -ef | grep tomcat
```

to see tomcat page content and process.
