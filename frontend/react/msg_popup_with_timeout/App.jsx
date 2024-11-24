import Toast from './Toast';
import React from "react";

function App() {
  let [toastOn, setToastOn] = React.useState(false);
  function handleEnrol() {
    setToastOn(true);

    setTimeout(() => {
      setToastOn(false);
    }, 3000);
  }

  return (
    <div id="app">
      {
        toastOn &&
        <Toast message={"toast message"} />
      }
      <article>
        <h2>React Course</h2>
        <p>
          A course that teaches you React from the ground up and in great depth!
        </p>
        <button onClick={handleEnrol}>Enrol</button>
      </article>
    </div>
  );
}

export default App;
