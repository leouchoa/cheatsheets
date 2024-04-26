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

## Named Template Files

They're [used to reduced code duplication](https://helm.sh/docs/chart_template_guide/named_templates/)
in a way that doesn't break the manifest file and are usually stored
in a file called `_helpers.tpl`.

An important point here is in regards to indenting. When adding your specs from
`_helpers.tpl` into the manifest, you can either used the `template` or `include`
functions. It is [suggested](https://helm.sh/docs/chart_template_guide/named_templates/#the-include-function)
to used the `include` function to get the correct formatting by adding the
`indent` action.

## Hook

You can add [hook functions](https://helm.sh/docs/topics/charts_hooks/) to run certain
tasks during a specific point of your deployment, for example to backup a database
before the app deployment. They're usually a yaml file that have a property called
annotations.
