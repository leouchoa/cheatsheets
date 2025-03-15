# Deployment Strategies

## Rolling Update

## Recreate

## Blue/Green

## Canary

Suppose a new deployment called `frontend-v2` has been created in the default
namespace using the image `kodekloud/webapp-color:v2`. This deployment will be
used to test a newer version of the same app.

Configure the deployment in such a way that the service called `frontend-service`
routes less than 20% of traffic to the new deployment. Do not increase
the replicas of the frontend deployment.

1. Check if both versions have a common label, like `app=frontend`, so that
the deploy service

2. If not yet, add the `app=frontend` as a selector in your deployed service.

3. Check if the proportion of pods per version matches the criteria. Otherwise
scale up/down the versions to match them:
`kubectl scale deployment --replicas=1 frontend-v2`.

Now here's an interesting situation: if version 2 works as intended, should
we scale it down to 0 pods or delete the deployment altogether?

Here are some arguments that scaling down a deployment to 0 replicas before
deleting could be better than deleting it right away:

- Preserving configuration: By scaling down to 0, we keep the deployment's
configuration intact. This means we can easily scale it back up if needed,
without having to recreate the deployment again.

- Rollback capability: If something goes wrong with `v2`, we can quickly scale
the `v1` deployment back up to restore service, without needing to redeploy or
reconfigure it.

- Resource management: Scaling down to 0 frees up resources (like CPU and memory)
while keeping the deployment's metadata and configuration in place. So it's not
a big deal in terms of resources.

- Testing and Staging: It allows for easy testing and staging environments
where you might want to switch between different versions of an application
without losing the setup.
