import React from "react";

export default function Workout({ title, description, time, onComplete }) {
  let [timerStarted, setTimerStarted] = React.useState(false)

  let timer = React.useRef();

  function handleStartWorkout() {
    timer.current = setTimeout(() => {
      onComplete(title);

    }, time * 1000);
    setTimerStarted(true);

  }

  function handleStopWorkout() {
    clearTimeout(timer.current)
    onComplete(title);
  }

  return (
    <article className="workout">
      <h3>{title}</h3>
      <p>{description}</p>
      <p>{time}</p>
      <p>
        <button onClick={handleStartWorkout}>Start</button>
        <button onClick={handleStopWorkout}>Stop</button>
      </p>
    </article>
  );
}
