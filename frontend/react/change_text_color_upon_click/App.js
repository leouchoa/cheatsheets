import React from "react";

// don't change the Component name "App"
export default function App() {
  let [buttonClicked, setButtonClicked] = React.useState(false);

  return (
    <div>
      <p className={buttonClicked ? "active" : undefined}>Style me!</p>
      <button onClick={() => setButtonClicked(true)}>Toggle style</button>
    </div>
  );
}
