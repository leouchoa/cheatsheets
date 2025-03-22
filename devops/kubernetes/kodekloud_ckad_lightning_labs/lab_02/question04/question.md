# Question

Create a single ingress resource called ingress-vh-routing. The resource should route HTTP traffic to multiple hostnames as specified below:

The service video-service should be accessible on <http://watch.ecom-store.com:30093/video>

The service apparels-service should be accessible on <http://apparels.ecom-store.com:30093/wear>

To ensure that the path is correctly rewritten for the backend service, add the following annotation to the resource:

nginx.ingress.kubernetes.io/rewrite-target: /

Here 30093 is the port used by the Ingress Controller
