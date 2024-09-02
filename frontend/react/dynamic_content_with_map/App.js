import React from "react";

import Todo from "./Todo";
import "./index.css";

export const DUMMY_TODOS = ["Learn React", "Practice React", "Profit!"];

export default function App() {
  return DUMMY_TODOS.map((x) => Todo(x));
}
