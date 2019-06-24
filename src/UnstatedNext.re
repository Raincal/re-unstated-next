module type Config = {
  type state;
  type value;
  let useHook: (~initialState: state=?, unit) => value;
};

module CreateContainer = (C: Config) => {
  let context = React.createContext(None);

  module ContextProvider = {
    let makeProps = (~value: C.value, ~children, ()) => {
      "value": Some(value),
      "children": children,
    };
    let make = React.Context.provider(context);
  };

  module Provider = {
    [@react.component]
    let make = (~children, ~initialState: option(C.state)=?) => {
      let value = C.useHook(~initialState?, ());
      <ContextProvider value> children </ContextProvider>;
    };
  };

  exception Component_Must_Be_Wrapped_With_Container_Provider;

  let useContainer = () => {
    let value = React.useContext(context);
    switch (value) {
    | Some(value) => value
    | None => raise(Component_Must_Be_Wrapped_With_Container_Provider)
    };
  };
};