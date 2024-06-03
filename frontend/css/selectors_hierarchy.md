# Hierarchy

Here is the logical order of selectors from least to most weight assigned:

- Type selectors (e.g., h1) and pseudo-elements (e.g., ::before).
- Class selectors (e.g., .example), attributes selectors
(e.g., [type="radio"]) and pseudo-classes (e.g., :hover).
- ID selectors (e.g., #example).
- `!important`: will override everything, but just creates more mess in the
code. Avoid using it, structure your code!
