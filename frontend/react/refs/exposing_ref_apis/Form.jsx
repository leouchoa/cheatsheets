import React from "react";

let Form = React.forwardRef(
  function Form({ }, ref) {

    let formRef = React.useRef();

    React.useImperativeHandle(ref, () => {
      return {
        clear() {
          formRef.current.reset();
        }
      };
    })

    return (
      <form ref={formRef}>
        <p>
          <label>Name</label>
          <input type="text" />
        </p>

        <p>
          <label>Email</label>
          <input type="email" />
        </p>
        <p id="actions">
          <button>Save</button>
        </p>
      </form>
    );
  }
)

export default Form;
