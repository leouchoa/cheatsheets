# The Document Object Model

Disclaimer: this text always fully taken from the [udacity frontend course](https://www.udacity.com/course/front-end-web-developer-nanodegree--nd0011).

## Translating HTML to the DOM

When you request a website, no matter what backend language is powering that
website, it will respond with HTML. This response is based on the HTML
specification which contains a specific set of rules for how browsers should
process the data they recieve.

The process works in this order:

1. HTML is received
2. HTML tags are converted to tokens
3. Tokens are converted to Nodes
4. Nodes are converted to the DOM

## The Details

The browser receives a stream of HTML. The bytes are run through a parsing
process that determines the different characters (e.g. the start tag character
`<,` an attribute like href, a closing angle bracket like `>).` After parsing
has occurred, a process called tokenization begins. Tokenization takes one
character at a time and builds up tokens. The tokens are:

- DOCTYPE
- start tag
- end tag
- comment
- character
- end-of-file

At this state, the browser has received the bytes that've been sent by a
server. The browser has converted the bytes to tags and has read through the
tags to create a list of tokens.

This list of tokens then goes through the tree construction stage. The output of
this stage is the DOM, a tree structure that captures the content and properties
of the HTML and all the relationships between the nodes, meaning a
full, parsed representation of the HTML.

By the way, remember that a JavaScript object is a tree-like structure that has
properties and values. So the DOM can be accessed using a special object
provided by the browser: `document`.

The DOM is not:

- part of the JavaScript language

The DOM is:

- constructed from the browser
- globally accessible by JavaScript code using the document object

The DOM is standardized by the W3C. There are a number of specifications that
make up the DOM, here are few:

- Core Specification
- Events Specification
- Style Specification
- Validation Specification
- Load and Save Specification

To see the full list of DOM specs, check out the standard at:
[https://www.w3.org](https://www.w3.org/standards/techs/dom#w3c_all).

## Resources

-
