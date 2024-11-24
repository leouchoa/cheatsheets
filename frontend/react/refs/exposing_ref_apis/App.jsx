import Form from './Form';
import React from "react";


export function App() {
  let form = React.useRef();

  function handleRestart() {
    form.current.clear();
  }

  return (
    <div id="app">
      <button onClick={handleRestart}>Restart</button>
      <Form ref={form} />
    </div>
  );
}

