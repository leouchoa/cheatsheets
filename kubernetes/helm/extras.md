# Extra Topics

## Functions

You can apply [functions](https://helm.sh/docs/chart_template_guide/function_list/#string-functions)
to your template values. Examples:

- quote: `{{ quote .Values.image.repo }}`
- trim: `{{ trim .Values.image.repo }}`
- lower: `{{ lower .Values.image.repo }}`

## Pipelines

Just like in linux you can pipe your function. For example, suppose in the
code bellow that `{{ .Values.image.repo }}` is ` cat `. Then the resulting string
after applying the functions would be `"CAT"`.

```yaml
{{ quote .Values.image.repo | trim | upper | quote }}
```

## Conditionals

You can [conditionally](https://helm.sh/docs/chart_template_guide/control_structures/#helm)
add a yaml block, based on criteria:

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: {{ .Release.Name }}-configmap
data:
  myvalue: "Hello World"
  drink: {{ .Values.favorite.drink | default "tea" | quote }}
  {{- if eq .Values.favorite.drink "coffee" }}
  mug: "true"
  {{- end }}

```
