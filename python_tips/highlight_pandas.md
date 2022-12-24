# Highlight Maximum of Column

```
def maximum_value_in_column(column):    

    highlight = 'background-color: palegreen;'
    default = ''

    maximum_in_column = column.max()

    # must return one string per cell in this column
    return [highlight if v == maximum_in_column else default for v in column]


df.style.apply(maximum_value_in_column, subset=[columns_to_be_highlighted_list], axis=0)

```

# Highlight Cell Based on Condition


```
def even_number_background(cell_value):

    highlight = 'background-color: darkorange;'
    default = ''

    if type(cell_value) in [float, int]:
        if cell_value % 2 == 0:
            return highlight
    return default

df.style.applymap(is_even_background)
```

# Sources

- [queirozf.com](https://queirozf.com/entries/pandas-dataframe-examples-styling-cells-and-conditional-formatting#highlight-cell-if-largest-in-column)
