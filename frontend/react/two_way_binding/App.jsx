import React from 'react';
import Review from "./Review.js"

// don't change the Component name "App"
function App() {
  let [studentName, setStudentName] = React.useState("")

  let [feedbackText, setFeedbackText] = React.useState("")

  function handleStudentName(event) {
    setStudentName(event.target.value)
  }

  function handleFeedbackText(event) {
    setFeedbackText(event.target.value)
  }

  return (
    <>
      <section id="feedback">
        <h2>Please share some feedback</h2>
        <p>
          <label>Your Feedback</label>
          <textarea onChange={handleFeedbackText} />
        </p>
        <p>
          <label>Your Name</label>
          <input type="text" onChange={handleStudentName} />
        </p>
      </section>
      <section id="draft">
        <h2>Your feedback</h2>

        <Review student={studentName} feedback={feedbackText} />

        <p>
          <button>Save</button>
        </p>
      </section>
    </>
  );
}

export default App;
