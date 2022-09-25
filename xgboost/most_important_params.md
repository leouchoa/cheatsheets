---
output: 
  html_document: 
    toc: yes
---

# How to Procede: Overall Guideline

The most important aspect of creating a good model is almost always in feature engineering and `Xgboost` has a lot of hyper-parameters to tune. But in reality there's not much improvement coming from tuning every one of them. 

So here's a list of hyper-parameters to tune at first. It's good practice to first establish a baseline model just from running the booster with default parameters, adjusted for you task, and then go to tuning phase.


## Most Important Hyperparameters

- `learning rate`: 
  - `range`: [0,1]
  - `typical final values`: usually [0.01 - 0.2] ,but can be even less then 0.01.
- `subsample`
  - recommended values: [0.5 - 0.9]
- `min child weight`
  - good range to try for tuning is [2–10] or up to 20.
- `max depth`: 
  - The typical values range is 3–10
  - but it rarely needs to be higher than 5–7.

## Second Most Important Hyperparameters

- `gamma`:
  - usually within [0–20].
- `colsample_by_tree`:
  - recommended values: [0.5 - 0.9]
- `reg_alpha` and `reg_lambda`:
  - if you want to tune them, try creating a log-uniform grid and search there. You'll be searching in a orders of magnitude grid.


# Considerations on How to Actually Tune correctly

## Histogram-based models

The histogram method basically categorizes the continuous variables to improve speed. Is it always better? I don't know, but the claim is that it usually doesn't make the model worse and dramatically increases speed, so it's worth trying, specially if training is taking too long.

For more information you can go to the original [lightgbm paper](https://papers.nips.cc/paper/2017/file/6449f44a102fde848669bdd9eb6b76fa-Paper.pdf) and [machine learning mastery](https://machinelearningmastery.com/histogram-based-gradient-boosting-ensembles/) for some nice experiments.

## Should I use Dart?

[Dart](http://www.jmlr.org/proceedings/papers/v38/korlakaivinayak15.pdf) is the same thing as dropout in neural networks. We not always use dropout right? Same goes for dart. It tries to prevent overfit, but the most important source of overfitting is usually outside, present in train/test splits and model drift. For more info go to [andrew ng's deep learning specialization playlist](https://www.youtube.com/watch?v=2BH49JG_sTs&list=PLkDaE6sCZn6E7jZ9sN_xHwSHOdjUxUW_b&index=17).

## Scikit-learn API vs Native XGBoost API



## Cross-Validation

There are a lot of ways you can cross-validate, depending on how much control you want to have on what to do inside the folds. This sometimes matters and sometimes it doesn't. The most recommended way is to implement your kfold logic and a good example can found [here in the section "What is the best way of doing cross-validation with XGBoost?"](https://towardsdatascience.com/20-burning-xgboost-faqs-answered-to-use-the-library-like-a-pro-f8013b8df3e4)

## Early Stopping

Early stopping is a way to prevent the model from overfitting. It will evaluate the loss of both training and validation sets but if the validation loss increases after a certain threshold, then training stops.

Early stopping is very useful and usually used with a high number of trees. That means that you set a high number for `n_estimators` or `n_rounds` and then let early stopping do its work. After that you can select the number of trees based on minimal loss.

The question that matters is: should I use early stopping in `kfold-cv`? I don't know, depends on how much resources and time you have. The reality is that fitting many trees in each of the K iterations may be too costly to experiment with. Imagine fitting not only 1000 trees per fold, but a sequence like [100,300,500,700,900] when K is 10. **That's a lot**, but if you can afford, I think it's nice. That being said you also treat it as a hyper-parameter and explore it jointly with other parameters.



https://mljar.com/blog/xgboost-early-stopping/

## About the Hyperparameters Correlations and Search Strategies

Yes the parameters have relationships between them and with the outcome (minimal loss). There are three common ways of going on about how to optimize:

i. grid search
ii. tune one a time
iii. A mix of both (hybrid approach)

If you choose to grid search the best model then there are some strategies of how to construct the grid and how to move within that grid. Some approaches can be found **here**. You can start with a courser grid to allow more exploration in the hyper-parameter space and narrow down options. Then you can either continue with a finer automated grid search or manually tune them.

If you choose to tune one a time, start with the most important parameters and then go to the less important. This strategy is nice because it provides faster model iterations and frees you from running large and long runs.


### Best Strategy

What's the best strategy? I don't know. Depends on your resources, constraints, setting and preferences. It's always good practice to differentiate between a `kaggle` challenge and a real life modeling scenario. In `kaggle` you can try whatever you want and get good results. In real life, you're trying to put a model into a production setting (that is actually serving it is a service to customers) and most of the times you'll want to have a more automated approach, with testing all over the place, and many times the grid search will be more convenient for that case.

That being said, it's recommended separate experimentation runs from production runs and have both integrated into you modeling routines. In a production run it's best to fall back to a more predictable approach (specially if you need an MVP model), while when experimenting you can tune one at a time, which is good to get a feel on the next steps and hyper-parameters correlation.

# Considerations on Making a Good Model

## Reproducibility

In `kaggle` you don't need to worry about much reproducibility, mostly because the train/test datasets are set for you. But in practice there's a lot of overburden regarding how you make your experiments (model optimization runs) comparable. 



# Sources

- [dataiku](https://blog.dataiku.com/narrowing-the-search-which-hyperparameters-really-matter)
- [Hyperparameter Importance Across Datasets](https://arxiv.org/abs/1710.04725)
- [20 Burning XGBoost FAQs Answered to Use the Library Like a Pro](https://towardsdatascience.com/20-burning-xgboost-faqs-answered-to-use-the-library-like-a-pro-f8013b8df3e4)
- [Cambridge Spark: Hyperparameter tuning in  xgboost](https://blog.cambridgespark.com/hyperparameter-tuning-in-xgboost-4ff9100a3b2f)