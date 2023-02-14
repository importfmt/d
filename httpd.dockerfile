FROM centos:7.9.2009
MAINTAINER 26n119e

EXPOSE 80
WORKDIR /opt
COPY httpd.out index.html /opt/
CMD ["/opt/httpd.out"]
