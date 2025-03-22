# Solution

Add this

```yaml
    livenessProbe:
      exec:
        command:
          - "sh"
          - "-c"
          - "ls /var/www/html/file_check"
      initialDelaySeconds: 10  # Delay before the first check
      periodSeconds: 60       # Check every 60 seconds
      failureThreshold: 3     # Restart after 3 consecutive failures
```
