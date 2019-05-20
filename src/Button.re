[@react.component]
let make = (~label, ~onClick) => {
  <button onClick> {ReasonReact.string(label)} </button>;
};