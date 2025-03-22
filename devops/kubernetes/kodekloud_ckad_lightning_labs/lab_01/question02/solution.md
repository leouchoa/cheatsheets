# Solution

Incoming or outgoing connections are not working because of network policy. In the default namespace, we deployed a default-deny network policy which is interrupting the incoming or outgoing connections.

Now, create a network policy called test-network-policy to allow the connections, as follows:-

apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
  name: test-network-policy
  namespace: default
spec:
  podSelector:
    matchLabels:
      run: secure-pod
  policyTypes:

- Ingress
  ingress:
- from:
  - podSelector:
        matchLabels:
          name: webapp-color
    ports:
  - protocol: TCP
      port: 80

then check the connectivity from the webapp-color pod to the secure-pod:-

root@controlplane:~$ kubectl exec -it webapp-color -- sh
/opt # nc -v -z -w 5 secure-service 80
