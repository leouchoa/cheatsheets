from sklearn.metrics import mean_squared_log_error
from sklearn.model_selection import KFold

N_FOLDS = 

cv = KFold(
    n_splits=N_FOLDS,
    shuffle=True,
    random_state=1121218,
)

fold = 0
scores = np.empty(N_FOLDS)
for train_idx, test_idx in cv.split(p_input, p_target):
    print(f"Started fold {fold}...")
    # Create the training sets from training indices
    X_cv_train, y_cv_train = p_input.iloc[train_idx], p_target.iloc[train_idx]
    # Create the test sets from test indices
    X_cv_test, y_cv_test = p_input.iloc[test_idx], p_target.iloc[test_idx]
    # Init/fit XGB
    model = xgb.XGBRegressor(
        objective="reg:squarederror", n_estimators=10000, learning_rate=0.05
    )
    model.fit(
        X_cv_train,
        y_cv_train,
        eval_set=[(X_cv_test, y_cv_test)],
        early_stopping_rounds=50,
        verbose=False,
    )
    # Generate preds, evaluate
    preds = model.predict(X_cv_test)
    rmsle = np.sqrt(mean_squared_log_error(y_cv_test, preds))
    print("RMSLE of fold {}: {:.4f}\n".format(fold, rmsle))
    scores[fold] = rmsle
    fold += 1

print("Overall RMSLE: {:.4f}".format(np.mean(scores)))
