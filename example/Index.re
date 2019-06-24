type counter = {
  count: int,
  decrement: unit => unit,
  increment: unit => unit,
};

let useCounter = (~initialState=0, ()) => {
  let (count, setCount) = React.useState(_ => initialState);
  let decrement = () => setCount(_ => count - 1);
  let increment = () => setCount(_ => count + 1);
  {count, decrement, increment};
};

module Counter =
  UnstatedNext.CreateContainer({
    type state = int;
    type value = counter;
    let useHook = useCounter;
  });

module CounterDisplay = {
  [@react.component]
  let make = () => {
    let counter = Counter.useContainer();
    <>
      <button onClick={_ => counter.decrement()}>
        {React.string("-")}
      </button>
      <span> {React.string(string_of_int(counter.count))} </span>
      <button onClick={_ => counter.increment()}>
        {React.string("+")}
      </button>
    </>;
  };
};

module App = {
  [@react.component]
  let make = () =>
    <Counter.Provider>
      <CounterDisplay />
      <Counter.Provider initialState=2>
        <div> <div> <CounterDisplay /> </div> </div>
      </Counter.Provider>
    </Counter.Provider>;
};

ReactDOMRe.renderToElementWithId(<App />, "app");