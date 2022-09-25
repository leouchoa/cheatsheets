---
output: 
  html_document: 
    toc: yes
---
# Source

I've literally copied+pasted from this [kaggle notebook](https://www.kaggle.com/prashant111/a-guide-on-xgboost-hyperparameters-tuning)

## Hyperparameters


# 2.2 Booster Parameters



  - we have 2 types of boosters - tree booster and linear booster.
  - we will limit our discussion to tree booster because it always outperforms the linear booster and thus the later is rarely used.
  - lease visit, Parameters for Tree Booster, for detailed discussion on booster parameters.

## 2.2.1 eta



  - eta [default=0.3, alias: learning_rate]
    - It is analogous to learning rate in GBM.
    - It is the step size shrinkage used in update to prevent overfitting.
    - After each boosting step, we can directly get the weights of new features, and eta shrinks the feature weights to make the boosting process more conservative.
    - It makes the model more robust by shrinking the weights on each step.
    - range : [0,1]
    - Typical final values : 0.01-0.2.

## 2.2.2 gamma



  - gamma [default=0, alias: min_split_loss]
    - A node is split only when the resulting split gives a positive reduction in the loss function.
    - Gamma specifies the minimum loss reduction required to make a split.
    - It makes the algorithm conservative. The values can vary depending on the loss function and should be tuned.
    - The larger gamma is, the more conservative the algorithm will be.
    - Range: [0,∞]

## 2.2.3 max_depth



  - max_depth [default=6]
    - The maximum depth of a tree, same as GBM.
    - It is used to control over-fitting as higher depth will allow model to learn relations very specific to a particular sample.
    - Increasing this value will make the model more complex and more likely to overfit.
    - The value 0 is only accepted in lossguided growing policy when tree_method is set as hist and it indicates no limit on depth.
    - We should be careful when setting large value of max_depth because XGBoost aggressively consumes memory when training a deep tree.
    - range: [0,∞] (0 is only accepted in lossguided growing policy when tree_method is set as hist).
    - Should be tuned using CV.
    - Typical values: 3-10

## 2.2.4 min_child_weight



  - min_child_weight [default=1]
    - It defines the minimum sum of weights of all observations required in a child.
    - This is similar to min_child_leaf in GBM but not exactly. This refers to min “sum of weights” of observations while GBM has min “number of observations”.
    - It is used to control over-fitting.
    - Higher values prevent a model from learning relations which might be highly specific to the particular sample selected for a tree.
    - Too high values can lead to under-fitting.
    - Hence, it should be tuned using CV.
    - The larger min_child_weight is, the more conservative the algorithm will be.
    - range: [0,∞]

## 2.2.5 max_delta_step



  - max_delta_step [default=0]
    - In maximum delta step we allow each tree’s weight estimation to be.
    - If the value is set to 0, it means there is no constraint.
    - If it is set to a positive value, it can help making the update step more conservative.
    - Usually this parameter is not needed, but it might help in logistic regression when class is extremely imbalanced.
    - Set it to value of 1-10 might help control the update.
    - range: [0,∞]

## 2.2.6 subsample



  - subsample [default=1]
    - It denotes the fraction of observations to be randomly samples for each tree.
    - Subsample ratio of the training instances.
    - Setting it to 0.5 means that XGBoost would randomly sample half of the training data prior to growing trees. - This will prevent overfitting.
    - Subsampling will occur once in every boosting iteration.
    - Lower values make the algorithm more conservative and prevents overfitting but too small values might lead to under-fitting.
    - Typical values: 0.5-1
    - range: (0,1]

## 2.2.7 colsample_bytree, colsample_bylevel, colsample_bynode



  - colsample_bytree, colsample_bylevel, colsample_bynode [default=1]

    - This is a family of parameters for subsampling of columns.

    - All colsample_by parameters have a range of (0, 1], the default value of 1, and specify the fraction of columns to be subsampled.

    - colsample_bytree is the subsample ratio of columns when constructing each tree. Subsampling occurs once for every tree constructed.

    - colsample_bylevel is the subsample ratio of columns for each level. Subsampling occurs once for every new depth level reached in a tree. Columns are subsampled from the set of columns chosen for the current tree.

    - colsample_bynode is the subsample ratio of columns for each node (split). Subsampling occurs once every time a new split is evaluated. Columns are subsampled from the set of columns chosen for the current level.

    - colsample_by* parameters work cumulatively. For instance, the combination {'colsample_bytree':0.5, 'colsample_bylevel':0.5, 'colsample_bynode':0.5} with 64 features will leave 8 features to choose from at each split.

## 2.2.8 lambda



  - lambda [default=1, alias: reg_lambda]
    - L2 regularization term on weights (analogous to Ridge regression).
    - This is used to handle the regularization part of XGBoost.
    - Increasing this value will make model more conservative.

## 2.2.9 alpha



  - alpha [default=0, alias: reg_alpha]
    - L1 regularization term on weights (analogous to Lasso regression).
    - It can be used in case of very high dimensionality so that the algorithm runs faster when implemented.
    - Increasing this value will make model more conservative.

## 2.2.10 tree_method



  - tree_method string [default= auto]

    - The tree construction algorithm used in XGBoost.

    - XGBoost supports approx, hist and gpu_hist for distributed training. Experimental support for external memory is available for approx and gpu_hist.

    - Choices: auto, exact, approx, hist, gpu_hist

      - auto: Use heuristic to choose the fastest method.

        - For small to medium dataset, exact greedy (exact) will be used.

        - For very large dataset, approximate algorithm (approx) will be chosen.

        - Because old behavior is always use exact greedy in single machine, user will get a message when approximate algorithm is chosen to notify this choice.

      - exact: Exact greedy algorithm.

      - approx: Approximate greedy algorithm using quantile sketch and gradient histogram.

      - hist: Fast histogram optimized approximate greedy algorithm. It uses some performance improvements such as bins caching.

      - gpu_hist: GPU implementation of hist algorithm.

## 2.2.11 scale_pos_weight



  - scale_pos_weight [default=1]
    - It controls the balance of positive and negative weights,
    - It is useful for imbalanced classes.
    - A value greater than 0 should be used in case of high class imbalance as it helps in faster convergence.
    - A typical value to consider: sum(negative instances) / sum(positive instances).

## 2.2.12 max_leaves


  - max_leaves [default=0]
    - Maximum number of nodes to be added.
    - Only relevant when grow_policy=lossguide is set.

  - here are other hyperparameters like sketch_eps,updater, refresh_leaf, process_type, grow_policy, max_bin, predictor and num_parallel_tree.

  - for detailed discussion of these hyperparameters, please visit Parameters for Tree Booster



# 2.3 Learning Task Parameters



- These parameters are used to define the optimization objective the metric to be calculated at each step.

- They are used to specify the learning task and the corresponding learning objective. The objective options are below:

## 2.3.1 objective



- objective [default=reg:squarederror]

- It defines the loss function to be minimized. Most commonly used values are given below:

    - reg:squarederror : regression with squared loss.

    - reg:squaredlogerror: regression with squared log loss 1/2[log(pred+1)−log(label+1)]2. - All input labels are required to be greater than -1.

    - reg:logistic : logistic regression

    - binary:logistic : logistic regression for binary classification, output probability

    - binary:logitraw: logistic regression for binary classification, output score before logistic transformation

    - binary:hinge : hinge loss for binary classification. This makes predictions of 0 or 1, rather than producing probabilities.

    - multi:softmax : set XGBoost to do multiclass classification using the softmax objective, you also need to set num_class(number of classes)

    - multi:softprob : same as softmax, but output a vector of ndata nclass, which can be further reshaped to ndata nclass matrix. The result contains predicted probability of each data point belonging to each class.

## 2.3.2 eval_metric



- eval_metric [default according to objective]

- The metric to be used for validation data.
- The default values are rmse for regression, error for classification and mean average precision for ranking.
- We can add multiple evaluation metrics.
- Python users must pass the metrices as list of parameters pairs instead of map.

- The most common values are given below -
    - rmse : root mean square error
    - mae : mean absolute error
    - logloss : negative log-likelihood
    - error : Binary classification error rate (0.5 threshold). It is calculated as #(wrong cases)/#(all cases). For the predictions, the evaluation will regard the instances with prediction value larger than 0.5 as positive instances, and the others as negative instances.
    - merror : Multiclass classification error rate. It is calculated as #(wrong cases)/#(all cases).
    - mlogloss : Multiclass logloss
    - auc: Area under the curve
    - aucpr : Area under the PR curve

## 2.3.3 seed



- seed [default=0]
    - The random number seed.
    - This parameter is ignored in R package, use set.seed() instead.
    - It can be used for generating reproducible results and also for parameter tuning.

