# Question

We have deployed a few pods in this cluster in various `namespaces`.
Inspect them and identify the pod which is not in a Ready state. Troubleshoot and
fix the issue.

Next, add a check to restart the container on the same pod if the command
`ls /var/www/html/file_check` fails. This check should start after a delay
of 10 seconds and run every 60 seconds.
