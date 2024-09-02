import React from 'react';

// don't change the Component name "App"
export default function App() {
  let [buttonToggled, setButtonToggled] = React.useState(false)

  function handleToggleButton() {
    setButtonToggled(
      buttonToggled ? false : true
    )
  }

  let paragraphColor = buttonToggled ? { color: "red" } : { color: "white" }

  return (
    <div>
      <p style={paragraphColor}>Style me!</p>
      <button
        onClick={handleToggleButton}
      >
        Toggle style
      </button>
    </div>
  );
}

