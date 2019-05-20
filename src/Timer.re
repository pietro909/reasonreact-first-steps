type state = {
  seconds: int,
  isTicking: bool,
};

type action =
  | Start
  | Stop
  | Reset
  | Tick;

let styleDiv =
  ReactDOMRe.Style.make(
    ~border="1px solid black",
    ~borderRadius="8px",
    ~maxWidth="180px",
    ~textAlign="center",
    (),
  );

let styleP =
  ReactDOMRe.Style.make(
    ~color="#444444",
    ~fontSize="42px",
    ~margin="16px 0",
    (),
  );

[@react.component]
let make = () => {
  // this maps to Elm, each stateful component can be seen as
  // a nested update
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Start => {...state, isTicking: true}
        | Stop => {...state, isTicking: false}
        | Reset => {...state, seconds: 30}
        | Tick =>
          if (state.isTicking && state.seconds > 0) {
            {...state, seconds: state.seconds - 1};
          } else {
            {...state, isTicking: false};
          }
        },
      {isTicking: false, seconds: 30} // initial state
    );

  // "managed" effect: way better that side-effects in the rendering
  // function!
  React.useEffect(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);
    // clean up is
    // automatically called
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div style=styleDiv>
    <p style=styleP>
      {state.seconds |> Utils.formatTime |> ReasonReact.string}
    </p>
    <div>
      {state.isTicking
         ? <Button label="Stop" onClick={_event => dispatch(Stop)} />
         : <>
             <Button label="Start" onClick={_event => dispatch(Start)} />
             <Button label="Reset" onClick={_event => dispatch(Reset)} />
           </>}
    </div>
  </div>;
};